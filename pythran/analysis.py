'''
This module provides a few code analysis for the pythran language.
    * LocalDeclarations gathers declarations local to a node
    * GlobalDeclarations gathers top-level declarations
    * Locals computes the value of locals()
    * Globals computes the value of globals()
    * ImportedIds gathers identifiers imported by a node
    * ConstantExpressions gathers constant expression
    * Aliases gather aliasing informations
    * Identifiers gathers all identifiers used in a node
    * YieldPoints gathers all yield points from a node
    * BoundedExpressions gathers temporary objects
    * ArgumentEffects computes write effect on arguments
    * GlobalEffects computes function effect on global state
    * PureFunctions detects functions without side-effects.
    * ParallelMaps detects parallel map(...)
    * UsedDefChain build used-define chains analysis for each variable.
    * UseOMP detects if a function use OpenMP
    * HasBreak detects if a loop has a direct break
    * HasContinue detects if a loop has a direct continue
    * LazynessAnalysis returns number of time a name is use.
    * OptimizableComp finds whether a comprehension can be optimized.
    * PotentialIterator finds if it is possible to use an iterator.
    * ArgumentReadOnce counts the usages of each argument of each function
    * Ancestors computes the ancestors of each node
    * Scope computes scope information
    * Dependencies lists the functions and types required by a function
    * OrderedGlobalDeclarations order all global functions.
'''

from tables import modules, methods, functions
import ast
import networkx as nx
import metadata as md
import intrinsic
from passmanager import NodeAnalysis, FunctionAnalysis, ModuleAnalysis
from syntax import PythranSyntaxError
from itertools import product
import openmp
from collections import defaultdict
import math


##
class CFG(FunctionAnalysis):
    """
    Computes the Control Flow Graph of a function

    The processing of a node yields a pair containing
    * the OUT nodes, to be linked with the IN nodes of the successor
    * the RAISE nodes, nodes that stop the control flow (exception/break/...)
    """
    def __init__(self):
        self.result = nx.DiGraph()
        super(CFG, self).__init__()

    def visit_FunctionDef(self, node):
        # the function itself is the entry point
        self.result.add_node(node)
        currs = (node,)
        for n in node.body:
            self.result.add_node(n)
            for curr in currs:
                self.result.add_edge(curr, n)
            currs, _ = self.visit(n)
        # add an edge to None for nodes that end the control flow
        # without a return
        self.result.add_node(None)
        for curr in currs:
            self.result.add_edge(curr, None)
        #nx.draw_graphviz(self.result)
        #nx.write_dot(self.result, node.name + '.dot')

    def visit_Pass(self, node):
        """OUT = node, RAISES = ()"""
        return (node,), ()

    # All these nodes have the same behavior as pass
    visit_Assign = visit_AugAssign = visit_Import = visit_Pass
    visit_Expr = visit_Print = visit_ImportFrom = visit_Pass
    visit_Yield = visit_Delete = visit_Pass

    def visit_Return(self, node):
        """OUT = (), RAISES = ()"""
        return (), ()

    def visit_For(self, node):
        """
        OUT = (node,) + last body statements
        RAISES = body's that are not break or continue
        """
        currs = (node,)
        break_currs = (node,)
        raises = ()
        # handle body
        for n in node.body:
            self.result.add_node(n)
            for curr in currs:
                self.result.add_edge(curr, n)
            currs, nraises = self.visit(n)
            for nraise in nraises:
                if type(nraise) is ast.Break:
                    break_currs += (nraise,)
                elif type(nraise) is ast.Continue:
                    self.result.add_edge(nraise, node)
                else:
                    raises += (nraise,)
        # add the backward loop
        for curr in currs:
            self.result.add_edge(curr, node)
        # the else statement if needed
        if node.orelse:
            for n in node.orelse:
                self.result.add_node(n)
                for curr in currs:
                    self.result.add_edge(curr, n)
                currs, nraises = self.visit(n)
        return break_currs + currs, raises

    visit_While = visit_For

    def visit_If(self, node):
        """
        OUT = true branch U false branch
        RAISES = true branch U false branch
        """
        currs = (node,)
        raises = ()
        # true branch
        for n in node.body:
            self.result.add_node(n)
            for curr in currs:
                self.result.add_edge(curr, n)
            currs, nraises = self.visit(n)
            raises += nraises
        tcurrs = currs
        # false branch
        currs = (node,)
        for n in node.orelse:
            self.result.add_node(n)
            for curr in currs:
                self.result.add_edge(curr, n)
            currs, nraises = self.visit(n)
            raises += nraises
        return tcurrs + currs, raises

    def visit_Raise(self, node):
        """OUT = (), RAISES = (node)"""
        return (), (node,)

    visit_Break = visit_Continue = visit_Raise

    def visit_Assert(self, node):
        """OUT = RAISES = (node)"""
        return (node,), (node,)

    def visit_TryExcept(self, node):
        """
        OUT = body's U handler's
        RAISES = handler's
        this equation is not has good has it could be...
        but we need type information to be more accurate
        """
        currs = (node,)
        raises = ()
        for handler in node.handlers:
            self.result.add_node(handler)
        for n in node.body:
            self.result.add_node(n)
            for curr in currs:
                self.result.add_edge(curr, n)
            currs, nraises = self.visit(n)
            for nraise in nraises:
                if type(nraise) is ast.Raise:
                    for handler in node.handlers:
                        self.result.add_edge(nraise, handler)
                else:
                    raises += (nraise,)
        for handler in node.handlers:
            ncurrs, nraises = self.visit(handler)
            currs += ncurrs
            raises += nraises
        return currs, raises

    def visit_ExceptHandler(self, node):
        """OUT = body's, RAISES = body's"""
        currs = (node,)
        raises = ()
        for n in node.body:
            self.result.add_node(n)
            for curr in currs:
                self.result.add_edge(curr, n)
            currs, nraises = self.visit(n)
            raises += nraises
        return currs, raises


##
class LocalDeclarations(NodeAnalysis):
    """Gathers all local symbols from a function"""
    def __init__(self):
        self.result = set()
        super(LocalDeclarations, self).__init__()

    def visit_Assign(self, node):
        for t in node.targets:
            assert isinstance(t, ast.Name) or isinstance(t, ast.Subscript)
            if isinstance(t, ast.Name):
                self.result.add(t)

    def visit_For(self, node):
        assert isinstance(node.target, ast.Name)
        self.result.add(node.target)
        map(self.visit, node.body)


##
class GlobalDeclarations(ModuleAnalysis):
    """Generates a function name -> function node binding"""
    def __init__(self):
        self.result = dict()
        super(GlobalDeclarations, self).__init__()

    def visit_Import(self, node):
        self.result.update((a.name, a) for a in node.names)

    def visit_ImportFrom(self, node):
        self.result.update((a.asname or a.name, a) for a in node.names)

    def visit_FunctionDef(self, node):
        self.result[node.name] = node
        # no generic visit here, so no diving into function body


##
class Locals(ModuleAnalysis):
    """
    Statically compute the value of locals() before each statement

    Yields a dictionary binding every node to the set of variable names defined
    *before* this node.

    Following snippet illustrates its behavior:
    >>> import ast, passmanager
    >>> pm = passmanager.PassManager('test')
    >>> code = '''
    ... def b(n):
    ...     m = n + 1
    ...     def b(n):
    ...         return n + 1
    ...     return b(m)'''
    >>> tree = ast.parse(code)
    >>> l = pm.gather(Locals, tree)
    >>> l[tree.body[0].body[0]]
    set(['n'])
    >>> l[tree.body[0].body[1]]
    set(['b', 'm', 'n'])
    """

    def __init__(self):
        self.result = dict()
        self.locals = set()
        self.nesting = 0
        super(Locals, self).__init__()

    def generic_visit(self, node):
        super(Locals, self).generic_visit(node)
        if node not in self.result:
            self.result[node] = self.result[self.expr_parent]

    def store_and_visit(self, node):
        self.expr_parent = node
        self.result[node] = self.locals.copy()
        self.generic_visit(node)

    def visit_Module(self, node):
        self.expr_parent = node
        self.result[node] = self.locals
        map(self.visit, node.body)

    def visit_FunctionDef(self, node):
        # special case for nested functions
        if self.nesting:
            self.locals.add(node.name)
        self.nesting += 1
        self.expr_parent = node
        self.result[node] = self.locals.copy()
        parent_locals = self.locals.copy()
        map(self.visit, node.args.defaults)
        self.locals.update(arg.id for arg in node.args.args)
        map(self.visit, node.body)
        self.locals = parent_locals
        self.nesting -= 1

    def visit_Assign(self, node):
        self.expr_parent = node
        self.result[node] = self.locals.copy()
        self.visit(node.value)
        self.locals.update(t.id for t in node.targets
                           if isinstance(t, ast.Name))
        map(self.visit, node.targets)

    def visit_For(self, node):
        self.expr_parent = node
        self.result[node] = self.locals.copy()
        self.visit(node.iter)
        self.locals.add(node.target.id)
        map(self.visit, node.body)
        map(self.visit, node.orelse)

    def visit_Import(self, node):
        self.result[node] = self.locals.copy()
        self.locals.update(alias.name for alias in node.names)

    def visit_ImportFrom(self, node):
        self.result[node] = self.locals.copy()
        self.locals.update(alias.name for alias in node.names)

    def visit_ExceptHandler(self, node):
        self.expr_parent = node
        self.result[node] = self.locals.copy()
        if node.name:
            self.locals.add(node.name.id)
        node.type and self.visit(node.type)
        map(self.visit, node.body)

    # statements that do not define a new variable
    visit_Return = store_and_visit
    visit_Yield = store_and_visit
    visit_TryExcept = store_and_visit
    visit_AugAssign = store_and_visit
    visit_Print = store_and_visit
    visit_While = store_and_visit
    visit_If = store_and_visit
    visit_Raise = store_and_visit
    visit_Assert = store_and_visit
    visit_Expr = store_and_visit
    visit_Pass = store_and_visit
    visit_Break = store_and_visit
    visit_Continue = store_and_visit


##
class Globals(ModuleAnalysis):
    def __init__(self):
        self.result = set()
        super(Globals, self).__init__(GlobalDeclarations)

    def visit(self, node):
        pass  # everything is done by the run method

    def run(self, node, ctx):
        super(Globals, self).run(node, ctx)
        return set(self.global_declarations.keys()
                   + [i for i in modules if i.startswith('__')])


##
class ImportedIds(NodeAnalysis):
    """Gather ids referenced by a node and not declared locally"""
    def __init__(self):
        self.result = set()
        self.current_locals = set()
        self.is_list = False
        self.in_augassign = False
        super(ImportedIds, self).__init__(Globals, Locals)

    def visit_Name(self, node):
        if isinstance(node.ctx, ast.Store) and not self.in_augassign:
            self.current_locals.add(node.id)
        elif (node.id not in self.visible_globals
                and node.id not in self.current_locals):
            self.result.add(node.id)

    def visit_FunctionDef(self, node):
        self.current_locals.add(node.name)
        current_locals = self.current_locals.copy()
        self.current_locals.update(arg.id for arg in node.args.args)
        map(self.visit, node.body)
        self.current_locals = current_locals

    def visit_AnyComp(self, node):
        current_locals = self.current_locals.copy()
        map(self.visit, node.generators)
        self.visit(node.elt)
        self.current_locals = current_locals

    visit_ListComp = visit_AnyComp
    visit_SetComp = visit_AnyComp
    visit_DictComp = visit_AnyComp
    visit_GeneratorExp = visit_AnyComp

    def visit_Assign(self, node):
        #order matter as an assignation
        #is evaluted before being assigned
        self.visit(node.value)
        map(self.visit, node.targets)

    def visit_AugAssign(self, node):
        self.in_augassign = True
        self.generic_visit(node)
        self.in_augassign = False

    def visit_Lambda(self, node):
        current_locals = self.current_locals.copy()
        self.current_locals.update(arg.id for arg in node.args.args)
        self.visit(node.body)
        self.current_locals = current_locals

    def visit_Import(self, node):
        self.current_locals.update(alias.name for alias in node.names)

    def visit_ImportFrom(self, node):
        self.current_locals.update(alias.name for alias in node.names)

    def visit_Attribute(self, node):
        pass

    def prepare(self, node, ctx):
        super(ImportedIds, self).prepare(node, ctx)
        if self.is_list:  # so that this pass can be called on list
            node = node.body[0]
        self.visible_globals = set(self.globals) - self.locals[node]

    def run(self, node, ctx):
        if isinstance(node, list):  # so that this pass can be called on list
            self.is_list = True
            node = ast.If(ast.Num(1), node, [])
        return super(ImportedIds, self).run(node, ctx)


##
class ConstantExpressions(NodeAnalysis):
    """Identify constant expressions (dummy implementation)"""
    def __init__(self):
        self.result = set()
        super(ConstantExpressions, self).__init__(Globals, Locals,
                                                  PureFunctions, Aliases)

    def add(self, node):
        self.result.add(node)
        return True

    def visit_BoolOp(self, node):
        return all(map(self.visit, node.values)) and self.add(node)

    def visit_BinOp(self, node):
        rec = all(map(self.visit, (node.left, node.right)))
        return rec and self.add(node)

    def visit_UnaryOp(self, node):
        return self.visit(node.operand) and self.add(node)

    def visit_IfExp(self, node):
        rec = all(map(self.visit, (node.test, node.body, node.orelse)))
        return rec and self.add(node)

    def visit_Compare(self, node):
        rec = all(map(self.visit, [node.left] + node.comparators))
        return rec and self.add(node)

    def visit_Call(self, node):
        rec = all(map(self.visit, node.args + [node.func]))
        return rec and self.add(node)

    visit_Num = add
    visit_Str = add

    def visit_Subscript(self, node):
        rec = all(map(self.visit, (node.value, node.slice)))
        return rec and self.add(node)

    def visit_Name(self, node):
        if node in self.aliases:
            pure_fun = all(alias in self.pure_functions
                           for alias in self.aliases[node].aliases)
            return pure_fun and self.add(node)
        else:
            return False

    def visit_Attribute(self, node):
        def rec(w, n):
            if isinstance(n, ast.Name):
                return w[n.id]
            elif isinstance(n, ast.Attribute):
                return rec(w, n.value)[n.attr]
        return rec(modules, node).isconst() and self.add(node)

    def visit_Dict(self, node):
        rec = all(map(self.visit, node.keys + node.values))
        return rec and self.add(node)

    def visit_List(self, node):
        return all(map(self.visit, node.elts)) and self.add(node)

    visit_Tuple = visit_List
    visit_Set = visit_List

    def visit_Slice(self, node):
        # ultra-conservative, indeed
        return False

    def visit_Index(self, node):
        return self.visit(node.value) and self.add(node)


##
class OrderedGlobalDeclarations(ModuleAnalysis):
    '''Order all global functions according to their callgraph depth'''
    def __init__(self):
        self.result = dict()
        super(OrderedGlobalDeclarations, self).__init__(
            StrictAliases, GlobalDeclarations)

    def visit_FunctionDef(self, node):
        self.curr = node
        self.result[node] = set()
        self.generic_visit(node)

    def visit_Name(self, node):
        if node in self.strict_aliases:
            for alias in self.strict_aliases[node].aliases:
                if isinstance(alias, ast.FunctionDef):
                    self.result[self.curr].add(alias)
                elif isinstance(alias, ast.Call):  # this is a bind
                    for alias in self.strict_aliases[alias.args[0]].aliases:
                        self.result[self.curr].add(alias)

    def run(self, node, ctx):
        # compute the weight of each function
        # the weight of a function is the number functions it references
        super(OrderedGlobalDeclarations, self).run(node, ctx)
        old_count = -1
        new_count = 0
        # iteratively propagate weights
        while new_count != old_count:
            for k, v in self.result.iteritems():
                [v.update(self.result[f]) for f in list(v)]
            old_count = new_count
            new_count = reduce(lambda acc, s: acc + len(s),
                               self.result.itervalues(), 0)
        # return functions, the one with the greatest weight first
        return sorted(self.result.iterkeys(), reverse=True,
                      key=lambda s: len(self.result[s]))


##
class Aliases(ModuleAnalysis):
    """Gather aliasing informations across nodes."""
    class Info(object):
        def __init__(self, state, aliases):
            self.state = state
            self.aliases = aliases

    def __init__(self):
        self.result = dict()
        self.aliases = dict()
        super(Aliases, self).__init__(GlobalDeclarations)

    def expand_unknown(self, node):
        # should include built-ins too?
        unkowns = {None}.union(self.global_declarations.values())
        return unkowns.union(node.args)

    @staticmethod
    def access_path(node):
        def rec(w, n):
            if isinstance(n, ast.Name):
                return w.get(n.id, n.id)
            elif isinstance(n, ast.Attribute):
                return rec(w, n.value)[n.attr]
            elif isinstance(n, ast.FunctionDef):
                return node.name
            else:
                return node
        return rec(modules, node)

    # aliasing created by expressions
    def add(self, node, values=None):
        if not values:  # no given target for the alias
            if isinstance(node, intrinsic.Intrinsic):
                values = {node}  # an Intrinsic always aliases to itself
            else:
                values = set()  # otherwise aliases to nothing
        assert isinstance(values, set)
        self.result[node] = Aliases.Info(self.aliases.copy(), values)
        return values

    def visit_OMPDirective(self, node):
        pass

    def visit_BoolOp(self, node):
        return self.add(node, set.union(*map(self.visit, node.values)))

    def visit_UnaryOp(self, node):
        self.generic_visit(node)
        return self.add(node)

    visit_BinOp = visit_UnaryOp
    visit_Compare = visit_UnaryOp

    def visit_IfExp(self, node):
        self.visit(node.test)
        rec = map(self.visit, [node.body, node.orelse])
        return self.add(node, set.union(*rec))

    def visit_Dict(self, node):
        self.generic_visit(node)
        return self.add(node)  # not very accurate

    def visit_Set(self, node):
        self.generic_visit(node)
        return self.add(node)  # not very accurate

    def call_return_alias(self, node):
        func = node.func
        aliases = set()
        if isinstance(func, ast.Attribute):
            _, signature = methods.get(func.attr,
                                       functions.get(func.attr,
                                                     [(None, None)])[0])
            if signature and signature.return_alias:
                aliases = signature.return_alias(node)
        elif isinstance(func, ast.Name):
            func_aliases = self.result[func].aliases
            for func_alias in func_aliases:
                signature = None
                if isinstance(func_alias, ast.FunctionDef):
                    _, signature = functions.get(
                        func_alias.name,
                        [(None, None)])[0]
                    if signature and signature.return_alias:
                        aliases.update(signature.return_alias(node))
                elif hasattr(func_alias, 'return_alias'):
                    aliases.update(func_alias.return_alias(node))
                else:
                    pass  # better thing to do ?
        [self.add(a) for a in aliases if a not in self.result]
        return aliases or self.expand_unknown(node)

    def visit_Call(self, node):
        self.generic_visit(node)
        f = node.func
        # special handler for bind functions
        if isinstance(f, ast.Attribute) and f.attr == "partial":
            return self.add(node, {node})
        else:
            return_alias = self.call_return_alias(node)
            # expand collected aliases
            all_aliases = set()
            for value in return_alias:
                if value is None:
                    all_aliases.add(None)
                elif value in self.result:
                    all_aliases.update(self.result[value].aliases)
                else:
                    try:
                        ap = Aliases.access_path(value)
                        all_aliases.update(self.aliases.get(ap, ()))
                    except NotImplementedError:
                        # should we do something better here?
                        all_aliases.add(value)
                        pass
            return_alias = all_aliases
            return self.add(node, return_alias)

    visit_Num = visit_UnaryOp
    visit_Str = visit_UnaryOp

    def visit_Attribute(self, node):
        return self.add(node, {Aliases.access_path(node)})

    def visit_Subscript(self, node):
        self.generic_visit(node)
        # could be enhanced through better handling of containers
        return self.add(node)

    def visit_Name(self, node):
        if node.id not in self.aliases:
            err = ("identifier {0} unknown, either because "
                   "it is an unsupported intrinsic, "
                   "the input code is faulty, "
                   "or... pythran is buggy.")
            raise PythranSyntaxError(err.format(node.id), node)
        return self.add(node, self.aliases[node.id].copy())

    def visit_List(self, node):
        self.generic_visit(node)
        return self.add(node)  # not very accurate

    def visit_Tuple(self, node):
        self.generic_visit(node)
        return self.add(node)  # not very accurate

    def visit_comprehension(self, node):
        self.aliases[node.target.id] = {node.target}
        self.generic_visit(node)

    def visit_ListComp(self, node):
        map(self.visit_comprehension, node.generators)
        self.visit(node.elt)
        return self.add(node)

    visit_SetComp = visit_ListComp

    visit_GeneratorExp = visit_ListComp

    def visit_DictComp(self, node):
        map(self.visit_comprehension, node.generators)
        self.visit(node.key)
        self.visit(node.value)
        return self.add(node)

    # aliasing created by statements

    def visit_FunctionDef(self, node):
        self.aliases = dict()
        for module in modules:
            self.aliases.update((v, {v})
                                for k, v in modules[module].iteritems())
        self.aliases.update((f.name, {f})
                            for f in self.global_declarations.itervalues())
        self.aliases.update((arg.id, {arg})
                            for arg in node.args.args)
        self.generic_visit(node)

    def visit_Assign(self, node):
        value_aliases = self.visit(node.value)
        for t in node.targets:
            if isinstance(t, ast.Name):
                self.aliases[t.id] = value_aliases or {t}
                for alias in list(value_aliases):
                    if isinstance(alias, ast.Name):
                        self.aliases[alias.id].add(t)
            else:
                self.visit(t)

    def visit_For(self, node):
        self.aliases[node.target.id] = {node.target}
        # Error may come from false branch evaluation so we have to try again
        try:
            self.generic_visit(node)
        except PythranSyntaxError:
            self.generic_visit(node)

    def visit_While(self, node):
        # Error may come from false branch evaluation so we have to try again
        try:
            self.generic_visit(node)
        except PythranSyntaxError:
            self.generic_visit(node)

    def visit_If(self, node):
        self.visit(node.test)
        false_aliases = {k: v.copy() for k, v in self.aliases.iteritems()}
        try:  # first try the true branch
            map(self.visit, node.body)
            true_aliases, self.aliases = self.aliases, false_aliases
        except PythranSyntaxError:  # it failed, try the false branch
            map(self.visit, node.orelse)
            raise  # but still throw the exception, maybe we are in a For
        try:  # then try the false branch
            map(self.visit, node.orelse)
        except PythranSyntaxError:  # it failed
            # we still get some info from the true branch, validate them
            self.aliases = true_aliases
            raise  # and let other visit_ handle the issue
        for k, v in true_aliases.iteritems():
            if k in self.aliases:
                self.aliases[k].update(v)
            else:
                assert isinstance(v, set)
                self.aliases[k] = v

    def visit_ExceptHandler(self, node):
        if node.name:
            self.aliases[node.name.id] = {node.name}
        self.generic_visit(node)


##
class StrictAliases(Aliases):
    """
    Gather aliasing informations across nodes,
    without adding unsure aliases.
    """
    def expand_unknown(self, node):
        return {}


##
class Identifiers(NodeAnalysis):
    """Gather all identifiers used throughout a node."""
    def __init__(self):
        self.result = set()
        super(Identifiers, self).__init__()

    def visit_Name(self, node):
        self.result.add(node.id)

    def visit_FunctionDef(self, node):
        self.result.add(node.name)
        self.generic_visit(node)

    def visit_ImportFrom(self, node):
        self.generic_visit(node)
        self.result.add(node.module)

    def visit_alias(self, node):
        self.result.add(node.name)
        if node.asname:
            self.result.add(node.asname)


##
class YieldPoints(FunctionAnalysis):
    '''Gathers all yield points of a generator, if any.'''
    def __init__(self):
        self.result = list()
        super(YieldPoints, self).__init__()

    def visit_Yield(self, node):
        self.result.append(node)


##
class BoundedExpressions(ModuleAnalysis):
    '''Gathers all nodes that are bound to an identifier.'''

    Boundable = (
        ast.Name,
        ast.Subscript,
        ast.BoolOp,
        )

    def __init__(self):
        self.result = set()
        super(BoundedExpressions, self).__init__()

    def isboundable(self, node):
        return any(isinstance(node, t) for t in BoundedExpressions.Boundable)

    def visit_Assign(self, node):
        self.result.add(node.value)
        if self.isboundable(node.value):
            self.result.add(node.value)
        self.generic_visit(node)

    def visit_Call(self, node):
        for n in node.args:
            if self.isboundable(n):
                self.result.add(n)
        self.generic_visit(node)

    def visit_Return(self, node):
        node.value and self.visit(node.value)
        if node.value:
            self.result.add(node.value)
            if self.isboundable(node.value):
                self.result.add(node.value)
        self.generic_visit(node)

    def visit_BoolOp(self, node):
        if node in self.result:
            self.result.update(node.values)
        self.generic_visit(node)

    def visit_Subscript(self, node):
        if node in self.result:
            self.result.add(node.slice)


##
class ArgumentEffects(ModuleAnalysis):
    '''Gathers inter-procedural effects on function arguments.'''
    class FunctionEffects(object):
        def __init__(self, node):
            self.func = node
            if isinstance(node, ast.FunctionDef):
                self.update_effects = [False] * len(node.args.args)
            elif isinstance(node, intrinsic.Intrinsic):
                self.update_effects = [isinstance(x, intrinsic.UpdateEffect)
                                       for x in node.argument_effects]
            elif isinstance(node, ast.alias):
                self.update_effects = []
            elif isinstance(node, intrinsic.Class):
                self.update_effects = []
            else:
                raise NotImplementedError

    class ConstructorEffects(object):
        def __init__(self, node):
            self.func = node
            self.update_effects = [False]

    def __init__(self):
        self.result = nx.DiGraph()
        self.node_to_functioneffect = dict()
        super(ArgumentEffects, self).__init__(Aliases, GlobalDeclarations)

    def prepare(self, node, ctx):
        super(ArgumentEffects, self).prepare(node, ctx)
        for n in self.global_declarations.itervalues():
            fe = ArgumentEffects.FunctionEffects(n)
            self.node_to_functioneffect[n] = fe
            self.result.add_node(fe)
        for m in modules:
            for name, intrinsic in modules[m].iteritems():
                fe = ArgumentEffects.FunctionEffects(intrinsic)
                self.node_to_functioneffect[intrinsic] = fe
                self.result.add_node(fe)
        self.all_functions = [fe.func for fe in self.result]

    def run(self, node, ctx):
        super(ArgumentEffects, self).run(node, ctx)
        keep_going = True  # very naive approach
        while keep_going:
            keep_going = False
            for function in self.result:
                for ue in enumerate(function.update_effects):
                    update_effect_index, update_effect = ue
                    if not update_effect:
                        continue
                    for pred in self.result.predecessors(function):
                        edge = self.result.edge[pred][function]
                        for fp in enumerate(edge["formal_parameters"]):
                            i, formal_parameter_index = fp
                            # propagate the impurity backward if needed.
                            # Afterward we may need another graph iteration
                            ith_effectiv = edge["effective_parameters"][i]
                            if (formal_parameter_index == update_effect_index
                                    and not pred.update_effects[ith_effectiv]):
                                pred.update_effects[ith_effectiv] = True
                                keep_going = True

        return {f.func: f.update_effects for f in self.result}

    def argument_index(self, node):
        while isinstance(node, ast.Subscript):
            node = node.value
        for node_alias in self.aliases[node].aliases:
            try:
                return self.current_function.func.args.args.index(node_alias)
            except ValueError:
                pass
        return -1

    def visit_FunctionDef(self, node):
        self.current_function = self.node_to_functioneffect[node]
        assert self.current_function in self.result
        self.generic_visit(node)

    def visit_AugAssign(self, node):
        n = self.argument_index(node.target)
        if n >= 0:
            self.current_function.update_effects[n] = True
        self.generic_visit(node)

    def visit_Assign(self, node):
        for t in node.targets:
            if isinstance(t, ast.Subscript):
                n = self.argument_index(t)
                if n >= 0:
                    self.current_function.update_effects[n] = True
        self.generic_visit(node)

    def visit_Call(self, node):
        for i, arg in enumerate(node.args):
            n = self.argument_index(arg)
            if n >= 0:
                func_aliases = self.aliases[node].state[
                    Aliases.access_path(node.func)]

                # expand argument if any
                func_aliases = reduce(
                    lambda x, y: x + (
                        self.all_functions
                        if (isinstance(y, ast.Name)
                            and self.argument_index(y) >= 0)
                        else [y]),
                    func_aliases,
                    list())

                for func_alias in func_aliases:
                    # special hook for binded functions
                    if isinstance(func_alias, ast.Call):
                        bound_name = func_alias.args[0].id
                        func_alias = self.global_declarations[bound_name]
                    func_alias = self.node_to_functioneffect[func_alias]
                    predecessors = self.result.predecessors(func_alias)
                    if self.current_function not in predecessors:
                        self.result.add_edge(
                            self.current_function,
                            func_alias,
                            effective_parameters=[],
                            formal_parameters=[])
                    edge = self.result.edge[self.current_function][func_alias]
                    edge["effective_parameters"].append(n)
                    edge["formal_parameters"].append(i)
        self.generic_visit(node)


##
class GlobalEffects(ModuleAnalysis):
    """Add a flag on each function that updates a global variable."""

    class FunctionEffect(object):
        def __init__(self, node):
            self.func = node
            if isinstance(node, ast.FunctionDef):
                self.global_effect = False
            elif isinstance(node, intrinsic.Intrinsic):
                self.global_effect = node.global_effects
            elif isinstance(node, ast.alias):
                self.global_effect = False
            elif isinstance(node, str):
                self.global_effect = False
            elif isinstance(node, intrinsic.Class):
                self.global_effect = False
            else:
                print type(node), node
                raise NotImplementedError

    def __init__(self):
        self.result = nx.DiGraph()
        self.node_to_functioneffect = dict()
        super(GlobalEffects, self).__init__(Aliases, GlobalDeclarations)

    def prepare(self, node, ctx):
        super(GlobalEffects, self).prepare(node, ctx)

        def register_node(n):
            fe = GlobalEffects.FunctionEffect(n)
            self.node_to_functioneffect[n] = fe
            self.result.add_node(fe)

        map(register_node, self.global_declarations.itervalues())
        for m in modules:
            map(register_node, modules[m].itervalues())
        self.all_functions = [fe.func for fe in self.result]

    def run(self, node, ctx):
        super(GlobalEffects, self).run(node, ctx)
        keep_going = True
        while keep_going:
            keep_going = False
            for function in self.result:
                if function.global_effect:
                    for pred in self.result.predecessors(function):
                        if not pred.global_effect:
                            keep_going = pred.global_effect = True
        return {f.func for f in self.result if f.global_effect}

    def visit_FunctionDef(self, node):
        self.current_function = self.node_to_functioneffect[node]
        assert self.current_function in self.result
        self.generic_visit(node)

    def visit_Print(self, node):
        self.current_function.global_effect = True

    def visit_Call(self, node):
        # try to get all aliases of the function, if possible
        # else use [] as a fallback
        ap = Aliases.access_path(node.func)
        func_aliases = self.aliases[node].state.get(ap, [])
        # expand argument if any
        func_aliases = reduce(
            lambda x, y: x + (self.all_functions
                              if isinstance(y, ast.Name) else [y]),
            func_aliases,
            list())
        for func_alias in func_aliases:
            # special hook for binded functions
            if isinstance(func_alias, ast.Call):
                bound_name = func_alias.args[0].id
                func_alias = self.global_declarations[bound_name]
            func_alias = self.node_to_functioneffect[func_alias]
            self.result.add_edge(self.current_function, func_alias)
        self.generic_visit(node)


##
class PureFunctions(ModuleAnalysis):
    '''Yields the set of pure functions'''
    def __init__(self):
        self.result = set()
        super(PureFunctions, self).__init__(ArgumentEffects, GlobalEffects)

    def run(self, node, ctx):
        super(PureFunctions, self).run(node, ctx)
        no_arg_effect = set()
        for func, ae in self.argument_effects.iteritems():
            if not any(ae):
                no_arg_effect.add(func)
        pure_functions = no_arg_effect.difference(self.global_effects)
        return pure_functions


##
class ParallelMaps(ModuleAnalysis):
    '''Yields the est of maps that could be parallel'''
    def __init__(self):
        self.result = set()
        super(ParallelMaps, self).__init__(PureFunctions, Aliases)

    def visit_Call(self, node):
        if all(alias == modules['__builtin__']['map']
                for alias in self.aliases[node.func].aliases):
            if all(self.pure_functions.__contains__(f)
                    for f in self.aliases[node.args[0]].aliases):
                self.result.add(node)

    def display(self, data):
        for node in data:
            print "I:", "{0} {1}".format(
                "call to the `map' intrinsic could be parallel",
                "(line {0})".format(node.lineno)
                )


##
class OptimizableComprehension(NodeAnalysis):
    """Find whether a comprehension can be optimized."""
    def __init__(self):
        self.result = set()
        super(OptimizableComprehension, self).__init__(Identifiers)

    def check_comprehension(self, iters):
        targets = {gen.target.id for gen in iters}
        optimizable = True

        for it in iters:
            ids = self.passmanager.gather(Identifiers, it, self.ctx)
            optimizable &= all(((ident == it.target.id)
                                | (ident not in targets)) for ident in ids)

        return optimizable

    def visit_ListComp(self, node):
        if (self.check_comprehension(node.generators)):
            self.result.add(node)

    def visit_GeneratorExp(self, node):
        if (self.check_comprehension(node.generators)):
            self.result.add(node)


##
class UsedDefChain(FunctionAnalysis):
    """Build used-define chains analysis for each variable.

       This analyse visit ast and build nodes each time it encounters an
       ast.Name node. It is a U (use) node when context is store and D (define)
       when context is Load or Param.
       This node is linked to all previous possible states in the program.
       Multiple state can happen when we use if-else statement, and loop
       can happen too with for and while statement.
       Result is a dictionary which associate a graph to the matching name.
    """
    def __init__(self):
        self.result = dict()
        self.current_node = dict()
        self.use_only = dict()
        self.in_loop = False
        self.break_ = dict()
        self.continue_ = dict()
        super(UsedDefChain, self).__init__(Globals)

    def merge_dict_set(self, into_, from_):
        for i in from_:
            if i in into_:
                into_[i].update(from_[i])
            else:
                into_[i] = from_[i]

    def add_loop_edges(self, prev_node):
        self.merge_dict_set(self.continue_, self.current_node)
        for id in self.continue_:
            if id in self.result:
                graph = self.result[id]
            else:
                graph = self.use_only[id]
            if id in prev_node and prev_node[id] != self.continue_[id]:
                entering_node = [i for j in prev_node[id]
                                 for i in graph.successors_iter(j)]
            else:
                cond = lambda x: graph.in_degree(x) == 0
                entering_node = filter(cond, graph)
            graph.add_edges_from(product(self.continue_[id],
                                 entering_node))
        self.continue_ = dict()

    def visit_Name(self, node):
        if node.id not in self.result and node.id not in self.use_only:
            if not (isinstance(node.ctx, ast.Store) or
                    isinstance(node.ctx, ast.Param)):
                if node.id not in self.globals:
                    err = "identifier {0} is used before assignment"
                    raise PythranSyntaxError(err.format(node.id), node)
                else:
                    self.use_only[node.id] = nx.DiGraph()
                    self.use_only[node.id].add_node("D0",
                                                    action="D", name=node)
            else:
                self.result[node.id] = nx.DiGraph()
                self.result[node.id].add_node("D0", action="D", name=node)
            self.current_node[node.id] = set(["D0"])
        else:
            if node.id in self.result:
                graph = self.result[node.id]
            else:
                graph = self.use_only[node.id]
            if (isinstance(node.ctx, ast.Store) or
                    isinstance(node.ctx, ast.Param)):
                if node.id in self.use_only:
                    err = ("identifier {0} has a global linkage and can't"
                           "be assigned")
                    raise PythranSyntaxError(err.format(node.id), node)
                node_name = "D{0}".format(len(graph))
                graph.add_node(node_name, action="D", name=node)
            elif isinstance(node.ctx, ast.Load):
                node_name = "U{0}".format(len(graph))
                graph.add_node(node_name, action="U", name=node)
            else:
                return  # Other context are unused and Del is ignored
            prev_nodes = self.current_node.get(node.id, set())
            edges_list = zip(prev_nodes, [node_name] * len(prev_nodes))
            graph.add_edges_from(edges_list)
            self.current_node[node.id] = set([node_name])

    def visit_Assign(self, node):
        # in assignation, left expression is compute before the assignation
        # to the right expression
        self.visit(node.value)
        map(self.visit, node.targets)

    def visit_AugAssign(self, node):
        self.visit(node.value)
        self.visit(node.target)
        var = node.target
        while isinstance(var, ast.Subscript):
            var = var.value
        if isinstance(var, ast.Name):
            var = var.id
        else:
            err = "AugAssign can't be used on {0}"
            raise PythranSyntaxError(err.format(var), node)
        last_node = self.current_node[var].pop()
        self.result[var].node[last_node]['action'] = "UD"
        self.current_node[var] = set([last_node])

    def visit_If(self, node):
        swap = False
        self.visit(node.test)

        #if an identifier is first used in orelse and we are in a loop,
        #we swap orelse and body
        undef = self.passmanager.gather(ImportedIds, node.body, self.ctx)
        if not all(i in self.current_node for i in undef) and self.in_loop:
            node.body, node.orelse = node.orelse, node.body
            swap = True

        #body
        old_node = {i: set(j) for i, j in self.current_node.iteritems()}
        map(self.visit, node.body)

        #orelse
        new_node = self.current_node
        self.current_node = old_node
        map(self.visit, node.orelse)

        if swap:
            node.body, node.orelse = node.orelse, node.body

        #merge result
        self.merge_dict_set(self.current_node, new_node)

    def visit_IfExp(self, node):
        swap = False
        self.visit(node.test)

        #if an identifier is first used in orelse and we are in a loop,
        #we swap orelse and body
        undef = self.passmanager.gather(ImportedIds, node.body, self.ctx)
        if undef and self.in_loop:
            node.body, node.orelse = node.orelse, node.body
            swap = True

        #body
        old_node = {i: set(j) for i, j in self.current_node.iteritems()}
        self.visit(node.body)

        #orelse
        new_node = self.current_node
        self.current_node = old_node
        self.visit(node.orelse)

        if swap:
            node.body, node.orelse = node.orelse, node.body

        #merge result
        self.merge_dict_set(self.current_node, new_node)

    def visit_Break(self, node):
        self.merge_dict_set(self.break_, self.current_node)

    def visit_Continue(self, node):
        self.merge_dict_set(self.continue_, self.current_node)

    def visit_While(self, node):
        prev_node = {i: set(j) for i, j in self.current_node.iteritems()}
        self.visit(node.test)
        #body
        self.in_loop = True
        old_node = {i: set(j) for i, j in self.current_node.iteritems()}
        map(self.visit, node.body)
        self.add_loop_edges(prev_node)
        self.in_loop = False

        #orelse
        new_node = self.current_node
        self.merge_dict_set(self.current_node, old_node)
        map(self.visit, node.orelse)

        #merge result
        self.merge_dict_set(self.current_node, new_node)
        self.merge_dict_set(self.current_node, self.break_)
        self.break_ = dict()

    def visit_For(self, node):
        self.visit(node.iter)

        #body
        self.in_loop = True
        old_node = {i: set(j) for i, j in self.current_node.iteritems()}
        self.visit(node.target)
        map(self.visit, node.body)
        self.add_loop_edges(old_node)
        self.in_loop = False

        #orelse
        new_node = self.current_node
        self.merge_dict_set(self.current_node, old_node)
        map(self.visit, node.orelse)

        #merge result
        self.merge_dict_set(self.current_node, new_node)
        self.merge_dict_set(self.current_node, self.break_)
        self.break_ = dict()

    def visit_TryExcept(self, node):

        #body
        all_node = dict()
        for stmt in node.body:
            self.visit(stmt)
            for k, i in self.current_node.iteritems():
                if k not in all_node:
                    all_node[k] = i
                else:
                    all_node[k].update(i)

        no_except = self.current_node

        #except
        for ex in node.handlers:
            self.current_node = dict(all_node)
            self.visit(ex)

            #merge result
            self.merge_dict_set(no_except, self.current_node)

        self.current_node = no_except

        if node.orelse:
            err = ("orelse should have been removed in previous passes")
            raise PythranSyntaxError(err, node)

    def visit_TryFinally(self, node):
        err = ("This node should have been removed in previous passes")
        raise PythranSyntaxError(err, node)


class UseOMP(FunctionAnalysis):
    """Detects if a function use openMP"""
    def __init__(self):
        self.result = False
        super(UseOMP, self).__init__()

    def visit_OMPDirective(self, node):
        self.result = True


class LazynessAnalysis(FunctionAnalysis):
    """
    Returns number of time a name is used. +inf if it is use in a
    loop, if a variable used to compute it is modify before
    its last use or if it is use in a function call (as it is not an
    interprocedural analysis)
    >>> import ast, passmanager, backend
    >>> code = "def foo(): c = 1; a = c + 2; c = 2; b = c + c + a; return b"
    >>> node = ast.parse(code)
    >>> pm = passmanager.PassManager("test")
    >>> res = pm.gather(LazynessAnalysis, node)
    >>> res['a'], res['b'], res['c']
    (inf, 1, 2)
    """
    def __init__(self):
        self.result = dict()
        self.name_count = dict()
        self.use = dict()
        self.dead = set()
        self.in_loop = False
        super(LazynessAnalysis, self).__init__(ArgumentEffects, Aliases)

    def modify(self, node, state):
        #if we modify a variable, all variables that needed it
        #to be compute are dead and its aliases too
        if isinstance(node, ast.Name):
            for var, deps in self.use.iteritems():
                for dep in deps:
                    if dep == node.id:
                        self.dead.add(var)
                        for alias in state[dep]:
                            self.dead.add(alias)
                        break

    def assign_to(self, node, from_, state):
        # a reassigned variable is not dead anymore
        if node.id in self.dead:
            self.dead.remove(node.id)
        # when we reassign a variable, we reinit all of its aliases
        # and save the result as a possible worse case
        if node.id in self.use:
            #gather value for alias node and other variables with same name
            state_name_count = filter(self.name_count.__contains__,
                                      state[node.id])
            alias_val = map(self.name_count.get, state_name_count)
            alias_val += [value for name, value in self.name_count.iteritems()
                          if name.id == node.id]
            ex_value = max(alias_val)
            if node.id in self.result:
                ex_value = max(self.result[node.id], ex_value)
            self.result[node.id] = ex_value
            for alias in state[node.id]:
                if alias in self.name_count:
                    self.name_count[alias] = 0
        self.name_count[node] = 0
        self.use[node.id] = set(from_)
        self.modify(node, state)

    def visit_FunctionDef(self, node):
        self.ids = self.passmanager.gather(Identifiers, node, self.ctx)
        self.generic_visit(node)

    def visit_Assign(self, node):
        self.visit(node.value)
        ids = self.passmanager.gather(Identifiers, node.value, self.ctx)
        for target in node.targets:
            if isinstance(target, ast.Name):
                self.assign_to(target, ids, self.aliases[node.value].state)
            elif isinstance(target, ast.Subscript):
                #if we modify just a part of a variable, it can't be lazy
                var_name = target.value
                while isinstance(var_name, ast.Subscript):
                    self.visit(var_name.slice)
                    var_name = var_name.value
                self.result[var_name.id] = float('inf')
            else:
                raise PythranSyntaxError("Assign to unknown node", node)

    def visit_AugAssign(self, node):
        #augassigned variable can't be lazy
        self.visit(node.value)
        if isinstance(node.target, ast.Name):
            self.result[node.target.id] = float('inf')
        elif isinstance(node.target, ast.Subscript):
            var_name = node.target.value
            while isinstance(var_name, ast.Subscript):
                var_name = var_name.value
            self.result[var_name.id] = float('inf')
        else:
            raise PythranSyntaxError("AugAssign to unknown node", node)

    def visit_Name(self, node):
        if isinstance(node.ctx, ast.Load) and node.id in self.use:
            name_from_id = [name for name in self.name_count.iterkeys()
                            if name.id == node.id]
            for alias in self.aliases[node].aliases.union(set(name_from_id)):
                # we only care about variable local to the function
                if isinstance(alias, ast.Name) and alias.id in self.ids:
                    if self.in_loop:
                        self.name_count[alias] = float('inf')
                    if node.id in self.dead:
                        # if a variable is dead, all it's aliases are dead too
                        self.dead.add(alias.id)  # PB: may be not the best
                        self.name_count[alias] = float('inf')
                    elif alias in self.name_count:
                        self.name_count[alias] += 1
        elif (isinstance(node.ctx, ast.Param) or
                isinstance(node.ctx, ast.Store)):
            #Store is only for exception
            self.name_count[node] = 0
            self.use[node.id] = set()

    def visit_If(self, node):
        self.visit(node.test)
        old_count = dict(self.name_count)
        old_dead = set(self.dead)
        old_deps = {a: set(b) for a, b in self.use.iteritems()}

        if isinstance(node.body, list):
            map(self.visit, node.body)
        else:
            self.visit(node.body)
        mid_count = self.name_count
        mid_dead = self.dead
        mid_deps = self.use

        self.name_count = old_count
        self.dead = old_dead
        self.use = old_deps
        if isinstance(node.orelse, list):
            map(self.visit, node.orelse)
        else:
            self.visit(node.orelse)

        #merge use variable
        for key in self.use:
            if key in mid_deps:
                self.use[key].update(mid_deps[key])
        for key in mid_deps:
            if key not in self.use:
                self.use[key] = set(mid_deps[key])

        #value is the worse case of both branches
        names = set(self.name_count.keys() + mid_count.keys())
        for name in names:
            val_body = mid_count.get(name, 0)
            val_else = self.name_count.get(name, 0)
            self.name_count[name] = max(val_body, val_else)

        #dead var are still dead
        self.dead.update(mid_dead)

    visit_IfExp = visit_If

    def visit_For(self, node):
        ids = self.passmanager.gather(Identifiers, node.iter, self.ctx)
        for id in ids:
            self.result[id] = float('inf')  # iterate value can't be lazy
        if isinstance(node.target, ast.Name):
            self.assign_to(node.target, ids, self.aliases[node.iter].state)
        else:
            err = "Assignation in for loop not to a Name"
            raise PythranSyntaxError(err, node)

        self.in_loop = True
        map(self.visit, node.body)
        self.in_loop = False

        map(self.visit, node.orelse)

    def visit_While(self, node):
        self.visit(node.test)

        self.in_loop = True
        map(self.visit, node.body)
        self.in_loop = False

        map(self.visit, node.orelse)

    def visit_Call(self, node):
        map(self.visit, node.args)
        #when there is an argument effet, we apply "modify" to the arg
        #and as it we don't know how it is modify, it is set to inf
        for fun in self.aliases[node.func].aliases:
            if isinstance(fun, ast.Call):
                fun = fun.args[0]
                for fun1 in self.aliases[fun].aliases:
                    for i, arg in enumerate(self.argument_effects[fun1]):
                        if len(node.args) != i:
                            break
                        elif arg:
                            self.modify(node.args[i],
                                        self.aliases[node.func].state)
            elif fun in self.argument_effects:
                for i, arg in enumerate(self.argument_effects[fun]):
                    if arg and len(node.args) > i:
                        self.modify(node.args[i],
                                    self.aliases[node.func].state)
                        if isinstance(node.args[i], ast.Name):
                            self.result[node.args[i].id] = float('inf')
            else:
                for arg in node.args:
                    self.modify(arg, self.aliases[node.func].state)

    def run(self, node, ctx):
        super(LazynessAnalysis, self).run(node, ctx)
        for name, val in self.name_count.iteritems():
            old_val = self.result.get(name.id, 0)
            self.result[name.id] = max(old_val, val)
        return self.result


class PotentialIterator(NodeAnalysis):
    """Find whether an expression can be replaced with an iterator."""
    def __init__(self):
        self.result = set()
        NodeAnalysis.__init__(self, Aliases, ArgumentReadOnce)

    def visit_For(self, node):
        self.result.add(node.iter)
        self.generic_visit(node)

    def visit_Compare(self, node):
        if type(node.ops[0]) in [ast.In, ast.NotIn]:
            self.result.update(node.comparators)
        self.generic_visit(node)

    def visit_Call(self, node):
        for i, arg in enumerate(node.args):
            isReadOnce = lambda f: (f in self.argument_read_once
                                    and self.argument_read_once[f][i] <= 1)
            if all(isReadOnce(alias)
                   for alias in self.aliases[node.func].aliases):
                self.result.add(arg)
        self.generic_visit(node)


##
class ArgumentReadOnce(ModuleAnalysis):
    '''Counts the usages of each argument of each function'''

    class FunctionEffects(object):
        def __init__(self, node):
            self.func = node
            self.dependencies = lambda ctx: 0
            if isinstance(node, ast.FunctionDef):
                self.read_effects = [-1] * len(node.args.args)
            elif isinstance(node, intrinsic.Intrinsic):
                self.read_effects = [
                    1 if isinstance(x, intrinsic.ReadOnceEffect)
                    else 2 for x in node.argument_effects]
            elif isinstance(node, ast.alias):
                self.read_effects = []
            elif isinstance(node, intrinsic.Class):
                self.read_effects = []
            else:
                raise NotImplementedError

    class ConstructorEffects(object):
        def __init__(self, node):
            self.func = node
            self.dependencies = lambda ctx: 0
            self.read_effects = [0]

    class Context(object):
        def __init__(self, function, index, path, global_dependencies):
            self.function = function
            self.index = index
            self.path = path
            self.global_dependencies = global_dependencies

    def __init__(self):
        self.result = set()
        self.node_to_functioneffect = dict()
        super(ArgumentReadOnce, self).__init__(Aliases, GlobalDeclarations)

    def prepare(self, node, ctx):
        super(ArgumentReadOnce, self).prepare(node, ctx)
        for n in self.global_declarations.itervalues():
            fe = ArgumentReadOnce.FunctionEffects(n)
            self.node_to_functioneffect[n] = fe
            self.result.add(fe)
        for m in modules:
            for name, intrinsic in modules[m].iteritems():
                fe = ArgumentReadOnce.FunctionEffects(intrinsic)
                self.node_to_functioneffect[intrinsic] = fe
                self.result.add(fe)
        self.all_functions = [fe.func for fe in self.result]

    def run(self, node, ctx):
        ModuleAnalysis.run(self, node, ctx)
        for fun in self.result:
            for i in xrange(len(fun.read_effects)):
                self.recursive_weight(fun, i, set())
        return {f.func: f.read_effects for f in self.result}

    def recursive_weight(self, function, index, predecessors):
        #TODO : Find out why it happens in some cases
        if len(function.read_effects) <= index:
            return 0
        if function.read_effects[index] == -1:
            # In case of recursive/cyclic calls
            cycle = function in predecessors
            predecessors.add(function)
            if cycle:
                function.read_effects[index] = 2 * function.dependencies(
                    ArgumentReadOnce.Context(function, index,
                                             predecessors, False))
            else:
                function.read_effects[index] = function.dependencies(
                    ArgumentReadOnce.Context(function, index,
                                             predecessors, True))
        return function.read_effects[index]

    def argument_index(self, node):
        while isinstance(node, ast.Subscript):
            node = node.value
        if node in self.aliases:
            for n_alias in self.aliases[node].aliases:
                try:
                    return self.current_function.func.args.args.index(n_alias)
                except ValueError:
                    pass
        return -1

    def local_effect(self, node, effect):
        index = self.argument_index(node)
        return lambda ctx: effect if index == ctx.index else 0

    def generic_visit(self, node):
        lambdas = map(self.visit, ast.iter_child_nodes(node))
        if lambdas:
            return lambda ctx: sum(l(ctx) for l in lambdas)
        else:
            return lambda ctx: 0

    def visit_FunctionDef(self, node):
        self.current_function = self.node_to_functioneffect[node]
        assert self.current_function in self.result
        self.current_function.dependencies = self.generic_visit(node)

    def visit_Return(self, node):
        dep = self.generic_visit(node)
        if isinstance(node.value, ast.Name):
            local = self.local_effect(node.value, 2)
            return lambda ctx: dep(ctx) + local(ctx)
        else:
            return dep

    def visit_Assign(self, node):
        dep = self.generic_visit(node)
        local = [self.local_effect(t, 2) for t in node.targets
                 if isinstance(t, ast.Subscript)]
        return lambda ctx: dep(ctx) + sum(l(ctx) for l in local)

    def visit_AugAssign(self, node):
        dep = self.generic_visit(node)
        local = self.local_effect(node.target, 2)
        return lambda ctx: dep(ctx) + local(ctx)

    def visit_For(self, node):
        iter_local = self.local_effect(node.iter, 1)
        iter_deps = self.visit(node.iter)
        body_deps = map(self.visit, node.body)
        else_deps = map(self.visit, node.orelse)
        return lambda ctx: iter_local(ctx) + iter_deps(ctx) + 2 * sum(
            l(ctx) for l in body_deps) + sum(l(ctx) for l in else_deps)

    def visit_While(self, node):
        test_deps = self.visit(node.test)
        body_deps = map(self.visit, node.body)
        else_deps = map(self.visit, node.orelse)
        return lambda ctx: test_deps(ctx) + 2 * sum(
            l(ctx) for l in body_deps) + sum(l(ctx) for l in else_deps)

    def visit_If(self, node):
        test_deps = self.visit(node.test)
        body_deps = map(self.visit, node.body)
        else_deps = map(self.visit, node.orelse)
        return lambda ctx: test_deps(ctx) + max(sum(
            l(ctx) for l in body_deps), sum(l(ctx) for l in else_deps))

    def visit_Call(self, node):
        l0 = self.generic_visit(node)
        index_corres = dict()
        func = None
        for i, arg in enumerate(node.args):
            n = self.argument_index(arg)
            if n >= 0:
                func_aliases = self.aliases[node].state[
                    Aliases.access_path(node.func)]

                # expand argument if any
                func_aliases = reduce(
                    lambda x, y: x + (
                        self.all_functions
                        if (isinstance(y, ast.Name)
                            and self.argument_index(y) >= 0)
                        else [y]),
                    func_aliases,
                    list())

                for func_alias in func_aliases:
                    # special hook for binded functions
                    if isinstance(func_alias, ast.Call):
                        bound_name = func_alias.args[0].id
                        func_alias = self.global_declarations[bound_name]
                    func_alias = self.node_to_functioneffect[func_alias]
                    index_corres[n] = i
                    func = func_alias

        return lambda ctx: l0(ctx) + self.recursive_weight(
            func, index_corres[ctx.index], ctx.path) if (
            (ctx.index in index_corres) and ctx.global_dependencies) else 0

    def visit_Subscript(self, node):
        dep = self.generic_visit(node)
        local = self.local_effect(node.value, 2)
        return lambda ctx: dep(ctx) + local(ctx)

    def visit_comprehension(self, node):
        dep = self.generic_visit(node)
        local = self.local_effect(node.iter, 1)
        return lambda ctx: dep(ctx) + local(ctx)


class HasBreak(NodeAnalysis):

    def __init__(self):
        self.result = False
        super(HasBreak, self).__init__()

    def visit_For(self, node):
        return

    def visit_Break(self, node):
        self.result = True


class HasContinue(NodeAnalysis):

    def __init__(self):
        self.result = False
        super(HasContinue, self).__init__()

    def visit_For(self, node):
        return

    def visit_Continue(self, node):
        self.result = True


class Ancestors(ModuleAnalysis):
    '''
    Associate each node with the list of its ancestors

    Based on the tree view of the AST: each node has the Module as parent.
    The result of this analysis is a dictionary with nodes as key,
    and list of nodes as values.
    '''

    def __init__(self):
        self.result = dict()
        self.current = list()
        super(Ancestors, self).__init__()

    def generic_visit(self, node):
        self.result[node] = list(self.current)
        self.current.append(node)
        super(Ancestors, self).generic_visit(node)
        self.current.pop()


class Scope(FunctionAnalysis):
    '''
    Associate each variable declaration with the node that defines it

    Whenever possible, associate the variable declaration to an assignment,
    otherwise to a node that defines a bloc (e.g. a For)
    This takes OpenMP information into accounts!
    The result is a dictionary with nodes as key and set of names as values
    '''

    def __init__(self):
        self.result = defaultdict(lambda: set())
        self.decl_holders = (ast.FunctionDef, ast.For,
                             ast.While, ast.TryExcept)
        super(Scope, self).__init__(Ancestors, UsedDefChain)

    def visit_OMPDirective(self, node):
        for dep in node.deps:
            if type(dep) is ast.Name:
                self.openmp_deps.setdefault(dep.id, []).append(dep)

    def visit_FunctionDef(self, node):
        # first gather some info about OpenMP declarations
        self.openmp_deps = dict()
        self.generic_visit(node)

        # then compute scope informations
        # unlike used-def chains, this takes OpenMP annotations into account
        for name, udgraph in self.used_def_chain.iteritems():
            # get all refs to that name
            refs = [udgraph.node[n]['name'] for n in udgraph]
            # add OpenMP refs (well, the parent of the holding stmt)
            refs.extend(self.ancestors[d][-3]   # -3 to get the right parent
                        for d in self.openmp_deps.get(name, []))
            # get their ancestors
            ancestors = map(self.ancestors.__getitem__, refs)
            # common ancestors
            prefixes = filter(lambda x: len(set(x)) == 1, zip(*ancestors))
            common = prefixes[-1][0]  # the last common ancestor

            # now try to attach the scope to an assignment.
            # This will be the first assignment found in the bloc
            if type(common) in self.decl_holders:
                # get all refs that define that name
                refs = [udgraph.node[n]['name']
                        for n in udgraph if udgraph.node[n]['action'] == 'D']
                refs.extend(self.openmp_deps.get(name, []))
                # get their parent
                prefs = set()
                for r in refs:
                    if type(self.ancestors[r][-1]) is openmp.OMPDirective:
                        # point to the parent of the stmt holding the metadata
                        prefs.add(self.ancestors[r][-4])
                    else:
                        prefs.add(self.ancestors[r][-1])
                # set the defining statement to the first assign in the body
                # unless another statements uses it before
                # or the common itselfs holds a dependency
                if common not in prefs:
                    for c in common.body:
                        if c in prefs:
                            if type(c) is ast.Assign:
                                common = c
                            break
            self.result[common].add(name)


class Dependencies(ModuleAnalysis):
    def __init__(self):
        self.result = set()
        super(Dependencies, self).__init__()

    def visit_List(self, node):
        self.result.add(('__builtin__', 'list'))
        self.generic_visit(node)

    def visit_Tuple(self, node):
        self.result.add(('__builtin__', 'tuple'))
        self.generic_visit(node)

    def visit_Set(self, node):
        self.result.add(('__builtin__', 'set'))
        self.generic_visit(node)

    def visit_Dict(self, node):
        self.result.add(('__builtin__', 'dict'))
        self.generic_visit(node)

    def visit_Str(self, node):
        self.result.add(('__builtin__', 'str'))
        self.generic_visit(node)

    def visit_Pow(self, node):
        self.result.add(('__builtin__', 'pow'))
        self.generic_visit(node)

    def visit_In(self, node):
        self.result.add(('__builtin__', 'in'))
        self.generic_visit(node)

    visit_NotIn = visit_In

    def visit_Is(self, node):
        self.result.add(('__builtin__', 'id'))
        self.generic_visit(node)

    visit_IsNot = visit_Is

    def visit_Print(self, node):
        self.result.add(('__builtin__', 'print'))
        self.generic_visit(node)

    def visit_Assert(self, node):
        self.result.add(('__builtin__', 'assert'))
        self.generic_visit(node)

    def visit_Yield(self, node):
        self.result.add(('types', 'generator'))
        self.generic_visit(node)

    def visit_Num(self, node):
        if type(node.n) is complex:
            self.result.add(('types', 'complex'))
        elif type(node.n) is long:
            self.result.add(('types', 'long'))
        elif math.isnan(node.n):
            self.result.add(('numpy', 'nan'))
        elif math.isinf(node.n):
            self.result.add(('numpy', 'inf'))

        self.generic_visit(node)

    def visit_Attribute(self, node):
        def rec(w, n):
            if isinstance(n, ast.Name):
                return (n.id,)
            elif isinstance(n, ast.Attribute):
                id = rec(w, n.value)
                if len(id) > 1:
                    plast, last = id[-2:]
                    if plast == '__builtin__' and last.startswith('__'):
                        id = id[:-2] + id[-1:]
                return id + (n.attr,)
        attr = rec(modules, node)

        attr and self.result.add(attr)
