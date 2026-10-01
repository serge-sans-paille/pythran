"""
CommonSubexpressionElimination hoists pure expressions that appear two or
more times in a function body into freshly named local temporaries, so the
C++ backend computes each value once.

The pass is conservative: it only acts when the rewrite is provably safe
under Pythran's purity, use-def, control-flow and OpenMP analyses.
"""

from copy import deepcopy

import gast as ast

from pythran.analyses import Ancestors, CFG, PureExpressions, UseDefChains
from pythran.analyses.repeated_expressions import (
    RepeatedExpressions, _gather_loaded_names, _operator_count)
from pythran.openmp import OMPDirective
from pythran.passmanager import Transformation
import pythran.graph as graph
import pythran.metadata as metadata


CSE_TEMP_PREFIX = "__cse"


def _index_block(block, parent, attr, holder_map):
    for index, stmt in enumerate(block):
        holder_map[id(stmt)] = (parent, attr, index)


def _index_statements(node, holder_map):
    """
    Build ``holder_map[id(stmt)] -> (parent, attr_name, index)`` for every
    statement under ``node``. The back-pointers live in a side dict so the
    AST itself is left untouched.
    """
    for attr in ("body", "orelse", "finalbody"):
        block = getattr(node, attr, None)
        if isinstance(block, list):
            _index_block(block, node, attr, holder_map)
            for child in block:
                _index_statements(child, holder_map)
    handlers = getattr(node, "handlers", None)
    if isinstance(handlers, list):
        for handler in handlers:
            _index_statements(handler, holder_map)


def _enclosing_statement(expr, ancestors, holder_map):
    """
    Walk ``expr``'s ancestor chain and return the first ancestor that the
    holder map knows about (i.e., the first statement under the function's
    block structure).
    """
    for ancestor in reversed(ancestors[expr]):
        if id(ancestor) in holder_map:
            return ancestor
    return None


def _shared_block(occurrences, ancestors, holder_map):
    """
    Return ``(parent, attr, statements, indices)`` for the statement-list
    holding every occurrence, or ``None`` when the occurrences are spread
    over several statement-lists. The hoisted assignment is inserted into
    this list so that it dominates every use.
    """
    enclosing = []
    for occurrence in occurrences:
        stmt = _enclosing_statement(occurrence, ancestors, holder_map)
        if stmt is None:
            return None
        enclosing.append(stmt)

    holders = [holder_map.get(id(stmt)) for stmt in enclosing]
    if any(holder is None for holder in holders):
        return None
    parent, attr, _ = holders[0]
    if any(holder[0] is not parent or holder[1] != attr
           for holder in holders[1:]):
        return None
    return parent, attr, enclosing, [holder[2] for holder in holders]


def _is_descendant(child_expr, parent_expr, ancestors):
    return id(parent_expr) in {id(node) for node in ancestors[child_expr]}


def _statement_assigned_names(stmt):
    """
    Return the set of identifier names that ``stmt`` writes to. Walking
    the local targets directly is cheaper than re-running ``IsAssigned``
    once per stability check, and stays consistent with how
    ``ForwardSubstitution`` checks for clobbers.
    """
    written = set()
    if isinstance(stmt, ast.Assign):
        for target in stmt.targets:
            for name in _walk_assignment_targets(target):
                written.add(name)
    elif isinstance(stmt, ast.AnnAssign):
        for name in _walk_assignment_targets(stmt.target):
            written.add(name)
    elif isinstance(stmt, ast.AugAssign):
        for name in _walk_assignment_targets(stmt.target):
            written.add(name)
    elif isinstance(stmt, (ast.For, ast.AsyncFor)):
        for name in _walk_assignment_targets(stmt.target):
            written.add(name)
    elif isinstance(stmt, ast.With):
        for item in stmt.items:
            if item.optional_vars is not None:
                for name in _walk_assignment_targets(item.optional_vars):
                    written.add(name)
    elif isinstance(stmt, ast.ExceptHandler):
        if stmt.name is not None:
            if isinstance(stmt.name, str):
                written.add(stmt.name)
            elif isinstance(stmt.name, ast.Name):
                written.add(stmt.name.id)
    elif isinstance(stmt, (ast.Global, ast.Nonlocal)):
        written.update(stmt.names)
    return written


def _walk_assignment_targets(target):
    if isinstance(target, ast.Name):
        yield target.id
    elif isinstance(target, (ast.Tuple, ast.List)):
        for elt in target.elts:
            yield from _walk_assignment_targets(elt)
    elif isinstance(target, ast.Starred):
        yield from _walk_assignment_targets(target.value)
    # Subscript and Attribute targets do not rebind a name in the
    # function's local scope; they mutate an existing object.


def _path_clears_operands(cfg, source_stmt, target_stmt, operands):
    """
    Return ``True`` if every CFG path from ``source_stmt`` to
    ``target_stmt`` only traverses statements that do not assign any of
    the names in ``operands``. ``source_stmt`` itself is the statement
    that produced the value, and ``target_stmt`` is the one that re-uses
    it; both are excluded from the read because the read happens before
    any write inside them.
    """
    if source_stmt is target_stmt:
        return True
    worklist = [source_stmt]
    seen = {id(source_stmt)}
    while worklist:
        current = worklist.pop()
        if current is target_stmt:
            continue
        for successor in cfg.successors(current):
            sid = id(successor)
            if sid in seen:
                continue
            seen.add(sid)
            if successor is target_stmt:
                continue
            if not graph.has_path(cfg, successor, target_stmt):
                continue
            written = _statement_assigned_names(successor)
            if written & operands:
                return False
            worklist.append(successor)
    return True


def _validate_operand_stability(occurrences, ancestors, cfg, holder_map):
    """
    Use the function-level CFG to confirm that no path between any two
    occurrences of the candidate expression assigns to one of the
    expression's operand names. When ``cfg`` is ``None`` (Pythran's CFG
    analysis does not cover every statement form) we conservatively
    fall back to a strict same-statement-list check that scans the
    sibling statements between the first and last occurrence.
    """
    operands = set()
    for occurrence in occurrences:
        operands |= _gather_loaded_names(occurrence)
    if not operands:
        return True

    statements = []
    for occurrence in occurrences:
        stmt = _enclosing_statement(occurrence, ancestors, holder_map)
        if stmt is None:
            return False
        statements.append(stmt)

    if cfg is None:
        # Conservative linear walk: every sibling statement between the
        # first and last occurrence must leave the operand names alone.
        holder = holder_map.get(id(statements[0]))
        if holder is None:
            return False
        parent, attr, _ = holder
        block = list(getattr(parent, attr))
        indices = [holder_map[id(stmt)][2] for stmt in statements]
        first_index = min(indices)
        last_index = max(indices)
        for stmt in block[first_index:last_index + 1]:
            if stmt in statements:
                continue
            written = _statement_assigned_names(stmt)
            if written & operands:
                return False
            for nested in ast.walk(stmt):
                if nested is stmt:
                    continue
                if isinstance(nested, ast.AST):
                    written = _statement_assigned_names(nested)
                    if written & operands:
                        return False
        return True

    for i, source_stmt in enumerate(statements):
        for target_stmt in statements[i + 1:]:
            if not _path_clears_operands(cfg, source_stmt, target_stmt,
                                         operands):
                return False
    return True


class _Substituter(ast.NodeTransformer):
    """
    Replace specific expression node identities with a freshly built
    ``Name(id=temp, ctx=Load())`` node. Identity is checked with ``is``
    so that two structurally equal expressions that are different AST
    objects are handled independently.
    """

    def __init__(self, targets, temp_name):
        self.targets = {id(target) for target in targets}
        self.temp_name = temp_name
        self.replaced = 0

    def visit(self, node):
        if id(node) in self.targets:
            self.replaced += 1
            return ast.Name(id=self.temp_name, ctx=ast.Load(),
                            annotation=None, type_comment=None)
        return super().visit(node)


class CommonSubexpressionElimination(Transformation[Ancestors, PureExpressions,
                                                    RepeatedExpressions,
                                                    UseDefChains]):
    """
    Hoist pure subexpressions that appear two or more times within a
    function body into a freshly named local variable.

    >>> import gast as ast
    >>> from pythran import passmanager, backend
    >>> pm = passmanager.PassManager("test")
    >>> code = '''
    ... def foo(a, b, c, d):
    ...     return (a + b) * c + (a + b) * d
    ... '''
    >>> node = ast.parse(code)
    >>> _, node = pm.apply(CommonSubexpressionElimination, node)
    >>> print(pm.dump(backend.Python, node))
    def foo(a, b, c, d):
        __cse0 = (a + b)
        return ((__cse0 * c) + (__cse0 * d))
    """

    def _scope_identifiers(self, function_node):
        """
        Every identifier used inside ``function_node`` (parameters, local
        writes and reads), so that a hoisted temporary cannot collide with
        an existing name.
        """
        names = set()
        for sub in ast.walk(function_node):
            if isinstance(sub, ast.Name):
                names.add(sub.id)
        return names

    def _filter_overlapping(self, occurrences, ancestors):
        """
        Discard occurrences that are descendants of an earlier kept
        occurrence in the same group. Without this guard, hoisting the
        smallest occurrence first would leave the larger one referencing
        a substituted name that no longer matches its fingerprint, and
        re-running the pass would loop forever.
        """
        kept = []
        for occurrence in occurrences:
            if any(_is_descendant(occurrence, prior, ancestors)
                   for prior in kept):
                continue
            kept.append(occurrence)
        return kept

    def _omp_protected(self, node, ancestors):
        for ancestor in ancestors[node]:
            if metadata.get(ancestor, OMPDirective):
                return True
        return False

    def _can_rewrite(self, occurrences, ancestors, cfg, holder_map):
        if any(self._omp_protected(occ, ancestors) for occ in occurrences):
            return False
        for occurrence in occurrences:
            stmt = _enclosing_statement(occurrence, ancestors, holder_map)
            if stmt is None:
                return False
            if isinstance(stmt, (ast.Global, ast.Nonlocal)):
                return False
            if metadata.get(stmt, OMPDirective):
                return False
        block = _shared_block(occurrences, ancestors, holder_map)
        if block is None:
            return False
        if not _validate_operand_stability(occurrences, ancestors, cfg,
                                           holder_map):
            return False
        return True

    def _fresh_name(self, scope_ids, used, counter):
        while True:
            candidate = "{}{}".format(CSE_TEMP_PREFIX, counter[0])
            counter[0] += 1
            if candidate in scope_ids or candidate in used:
                continue
            used.add(candidate)
            return candidate

    def _rewrite_group(self, occurrences, ancestors, scope_ids, used,
                       counter, holder_map):
        block = _shared_block(occurrences, ancestors, holder_map)
        if block is None:
            return False
        parent, attr, _, indices = block

        prototype = occurrences[0]
        first_index = min(indices)

        temp_name = self._fresh_name(scope_ids, used, counter)
        scope_ids.add(temp_name)

        prototype_copy = deepcopy(prototype)
        substituter = _Substituter(occurrences, temp_name)
        substituter.visit(parent)
        if substituter.replaced != len(occurrences):
            return False

        body = list(getattr(parent, attr))
        assignment = ast.Assign(
            targets=[ast.Name(id=temp_name, ctx=ast.Store(),
                              annotation=None, type_comment=None)],
            value=prototype_copy,
            type_comment=None,
        )
        body.insert(first_index, assignment)
        setattr(parent, attr, body)
        return True

    def _process_function(self, function_node):
        groups = self.passmanager.gather(RepeatedExpressions, function_node)
        if not groups:
            return False

        ancestors = self.gather(Ancestors, function_node)
        # Pythran's CFG analysis does not implement ``visit_With``; on
        # functions that contain a ``with`` statement, ``gather(CFG)``
        # raises. CSE therefore falls back to the per-Name use-def chain
        # check, which is strictly more conservative (it never permits
        # a rewrite that the CFG check would have rejected).
        try:
            cfg = self.gather(CFG, function_node)
        except TypeError:
            cfg = None
        holder_map = {}
        _index_statements(function_node, holder_map)

        scope_ids = self._scope_identifiers(function_node)
        used = set()
        counter = [0]

        # Process groups in OUTER-FIRST order: hoisting an outer
        # expression turns its inner occurrences into stale entries
        # whose count naturally falls below 2; the inner group is then
        # skipped on the next pass. Use the analysis-side operator
        # counter so the size metric stays consistent if other passes
        # consume RepeatedExpressions for their own decisions.
        sorted_groups = sorted(
            groups.values(),
            key=lambda occs: -_operator_count(occs[0]),
        )

        rewritten_any = False
        consumed_node_ids = set()
        for occurrences in sorted_groups:
            if any(id(n) in consumed_node_ids
                   for occ in occurrences for n in ast.walk(occ)):
                continue
            filtered = self._filter_overlapping(occurrences, ancestors)
            if len(filtered) < 2:
                continue
            if not self._can_rewrite(filtered, ancestors, cfg, holder_map):
                continue
            if self._rewrite_group(filtered, ancestors, scope_ids, used,
                                   counter, holder_map):
                rewritten_any = True
                for occurrence in filtered:
                    for descendant in ast.walk(occurrence):
                        consumed_node_ids.add(id(descendant))
        return rewritten_any

    def visit_Module(self, node):
        for stmt in node.body:
            if not isinstance(stmt, ast.FunctionDef):
                continue
            if self._process_function(stmt):
                self.update = True
        return node
