"""
RepeatedExpressions groups structurally identical pure subexpressions that
appear two or more times within the same function body.
"""

from collections import defaultdict, OrderedDict

import gast as ast

from pythran.analyses.ancestors import Ancestors
from pythran.analyses.pure_expressions import PureExpressions
from pythran.analyses.use_def_chain import UseDefChains
from pythran.openmp import OMPDirective
from pythran.passmanager import FunctionAnalysis
import pythran.metadata as metadata


_ATOMIC_TYPES = (ast.Name, ast.Constant)
_HOISTABLE_TYPES = (ast.BinOp, ast.UnaryOp, ast.BoolOp, ast.Compare,
                    ast.Call, ast.Attribute, ast.IfExp)
_FORBIDDEN_TYPES = (ast.Subscript, ast.List, ast.Tuple, ast.Set, ast.Dict,
                    ast.ListComp, ast.SetComp, ast.DictComp, ast.GeneratorExp,
                    ast.Lambda, ast.Yield, ast.YieldFrom, ast.Await,
                    ast.Starred, ast.JoinedStr, ast.FormattedValue,
                    ast.NamedExpr)


def _operator_fingerprint(op_node):
    return type(op_node).__name__


def _name_fingerprint(node, use_def_chains):
    """
    Return a name fingerprint that distinguishes occurrences of the same id
    bound to different definition points. Two ``Name`` occurrences must
    agree on their full definition set to be CSE-equivalent; otherwise the
    same id may refer to different runtime values and merging the
    surrounding expressions would be unsound.
    """
    chain = use_def_chains.get(node)
    if chain is None:
        return ("Name", node.id, ("__unbound__",))
    def_ids = sorted(id(d.node) for d in chain)
    return ("Name", node.id, tuple(def_ids))


def _expression_fingerprint(node, use_def_chains):
    """
    Compute a structural fingerprint suitable for hash-based grouping.
    Returns ``None`` for any node that may not be safely shared between
    two contexts.
    """
    if isinstance(node, _FORBIDDEN_TYPES):
        return None

    if isinstance(node, ast.Name):
        if not isinstance(node.ctx, ast.Load):
            return None
        return _name_fingerprint(node, use_def_chains)

    if isinstance(node, ast.Constant):
        return ("Constant", type(node.value).__name__, repr(node.value))

    if isinstance(node, ast.Attribute):
        if not isinstance(node.ctx, ast.Load):
            return None
        inner = _expression_fingerprint(node.value, use_def_chains)
        if inner is None:
            return None
        return ("Attribute", node.attr, inner)

    if isinstance(node, ast.BinOp):
        left = _expression_fingerprint(node.left, use_def_chains)
        right = _expression_fingerprint(node.right, use_def_chains)
        if left is None or right is None:
            return None
        return ("BinOp", _operator_fingerprint(node.op), left, right)

    if isinstance(node, ast.UnaryOp):
        operand = _expression_fingerprint(node.operand, use_def_chains)
        if operand is None:
            return None
        return ("UnaryOp", _operator_fingerprint(node.op), operand)

    if isinstance(node, ast.BoolOp):
        values = []
        for value in node.values:
            fp = _expression_fingerprint(value, use_def_chains)
            if fp is None:
                return None
            values.append(fp)
        return ("BoolOp", _operator_fingerprint(node.op), tuple(values))

    if isinstance(node, ast.Compare):
        left = _expression_fingerprint(node.left, use_def_chains)
        if left is None:
            return None
        ops = tuple(_operator_fingerprint(op) for op in node.ops)
        comparators = []
        for cmp_node in node.comparators:
            fp = _expression_fingerprint(cmp_node, use_def_chains)
            if fp is None:
                return None
            comparators.append(fp)
        return ("Compare", left, ops, tuple(comparators))

    if isinstance(node, ast.Call):
        func = _expression_fingerprint(node.func, use_def_chains)
        if func is None:
            return None
        args = []
        for arg in node.args:
            fp = _expression_fingerprint(arg, use_def_chains)
            if fp is None:
                return None
            args.append(fp)
        kwargs = []
        for keyword in node.keywords:
            fp = _expression_fingerprint(keyword.value, use_def_chains)
            if fp is None:
                return None
            kwargs.append((keyword.arg, fp))
        return ("Call", func, tuple(args), tuple(kwargs))

    if isinstance(node, ast.IfExp):
        test = _expression_fingerprint(node.test, use_def_chains)
        body = _expression_fingerprint(node.body, use_def_chains)
        orelse = _expression_fingerprint(node.orelse, use_def_chains)
        if test is None or body is None or orelse is None:
            return None
        return ("IfExp", test, body, orelse)

    return None


def _is_trivial(node):
    """
    A "trivial" expression names or denotes a value cheaply: a bare name, a
    constant, an attribute chain rooted at a name, or unary negation of one
    of those. Hoisting a trivial expression introduces an extra statement
    without saving any computation, so the CSE pass skips it.
    """
    if isinstance(node, _ATOMIC_TYPES):
        return True
    if isinstance(node, ast.Attribute):
        return _is_trivial(node.value)
    if isinstance(node, ast.UnaryOp) and isinstance(node.op, ast.USub):
        return _is_trivial(node.operand)
    return False


def _operator_count(node):
    """
    Return the number of operator/call nodes inside ``node`` (inclusive).

    The CSE pass uses this number to break ties between groups whose
    fingerprints are otherwise comparable: outer expressions have a
    larger operator count and are hoisted first.
    """
    total = 0
    for child in ast.walk(node):
        if isinstance(child, (ast.BinOp, ast.UnaryOp, ast.BoolOp,
                              ast.Compare, ast.Call, ast.IfExp)):
            total += 1
    return total


def _gather_loaded_names(node):
    """
    Return the set of identifiers ``node`` reads from. ``Store``/``Del``
    contexts are excluded so that augmented-assignment targets do not
    falsely report writes as reads.
    """
    loaded = set()
    for sub in ast.walk(node):
        if isinstance(sub, ast.Name) and isinstance(sub.ctx, ast.Load):
            loaded.add(sub.id)
    return loaded


def _children_with_conditionality(node, conditional):
    """
    Yield ``(child, conditional)`` for each child of ``node``, where
    ``conditional`` tells whether the child may be skipped, or evaluated
    later than the statement itself, when ``node`` is evaluated.
    """
    if isinstance(node, ast.BoolOp):
        for position, value in enumerate(node.values):
            yield value, conditional or position > 0
    elif isinstance(node, ast.IfExp):
        yield node.test, conditional
        yield node.body, True
        yield node.orelse, True
    elif isinstance(node, ast.Compare):
        yield node.left, conditional
        for position, comparator in enumerate(node.comparators):
            yield comparator, conditional or position > 0
    elif isinstance(node, ast.Assert):
        yield node.test, conditional
        if node.msg is not None:
            yield node.msg, True
    elif isinstance(node, ast.Lambda):
        for child in ast.iter_child_nodes(node):
            yield child, True
    elif isinstance(node, (ast.ListComp, ast.SetComp, ast.GeneratorExp,
                           ast.DictComp)):
        for position, generator in enumerate(node.generators):
            yield generator.iter, conditional or position > 0
            for target in (generator.target, *generator.ifs):
                yield target, True
        for child in ast.iter_child_nodes(node):
            if not isinstance(child, ast.comprehension):
                yield child, True
    else:
        for child in ast.iter_child_nodes(node):
            yield child, conditional


class RepeatedExpressions(FunctionAnalysis[Ancestors, PureExpressions,
                                           UseDefChains]):
    """
    For the visited ``FunctionDef``, return an ordered mapping
    ``fingerprint -> list[ast.AST]`` of pure, non-trivial expressions that
    appear at least twice. Each value list preserves source-order so that
    the first entry is the dominator-correct hoist site for a CSE rewrite.

    Expressions inside an OpenMP-protected statement, expressions in
    ``Store``/``Del``/``Param`` contexts, expressions whose operands are
    redefined between two uses (witnessed by mismatched use-def chains),
    and expressions of forbidden node kinds (``Subscript``, container
    literals, comprehensions, ``Lambda``, generator yields, ``NamedExpr``,
    starred forms, f-strings) are excluded. So are expressions that are not
    evaluated unconditionally when their statement runs: operands of a
    ``BoolOp`` after the first, comparators of a chained ``Compare`` after
    the first, the branches of an ``IfExp``, the message of an ``assert``, the
    body of a ``Lambda`` and the element and conditions of a comprehension.

    Groups are emitted in the source order of their first occurrence.
    """

    ResultType = OrderedDict

    def visit_FunctionDef(self, node):
        groups = defaultdict(list)
        first_seen_index = {}
        index = [0]

        def is_protected(expr):
            for ancestor in self.ancestors[expr]:
                if metadata.get(ancestor, OMPDirective):
                    return True
            return False

        def collect(expr, conditional=False):
            if not isinstance(expr, ast.AST):
                return
            if isinstance(expr, _FORBIDDEN_TYPES):
                for child, cond in _children_with_conditionality(
                        expr, conditional):
                    collect(child, cond)
                return
            if isinstance(expr, _HOISTABLE_TYPES) and not conditional:
                if expr in self.pure_expressions and not _is_trivial(expr):
                    if not is_protected(expr):
                        fp = _expression_fingerprint(expr,
                                                     self.use_def_chains)
                        if fp is not None:
                            if fp not in first_seen_index:
                                first_seen_index[fp] = index[0]
                            groups[fp].append(expr)
                            index[0] += 1
            for child, cond in _children_with_conditionality(expr,
                                                             conditional):
                collect(child, cond)

        for stmt in node.body:
            collect(stmt)

        for fp, occurrences in sorted(groups.items(),
                                      key=lambda kv: first_seen_index[kv[0]]):
            if len(occurrences) < 2:
                continue
            self.result[fp] = occurrences
