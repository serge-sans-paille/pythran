'''
This module provides a few code analysis for the pythran language.
    * LocalDeclarations gathers declarations local to a node
    * GlobalDeclarations gathers top-level declarations
    * Locals computes the value of locals()
    * Globals computes the value of globals()
    * ImportedIds gathers identifiers imported by a node
    * ConstantExpressions gathers constant expression
    * Aliases gather aliasing informations
    * Identifiers gathers all identifiers used in a module
    * YieldPoints gathers all yield points from a node
    * BoundedExpressions gathers temporary objects
    * ArgumentEffects computes write effect on arguments
    * GlobalEffects computes function effect on global state
    * PureFunctions detects functions without side-effects.
    * ParallelMaps detects parallel map(...)
    * OptimizableComp finds whether a comprehension can be optimized.
    * PotentialIterator finds if it is possible to use an iterator.
    * ArgumentReadOnce counts the usages of each argument of each function
'''

from tables import modules, builtin_constants, builtin_constructors
from tables import methods, functions
import ast
import networkx as nx
import metadata as md
import intrinsic
from passmanager import NodeAnalysis, FunctionAnalysis, ModuleAnalysis
from syntax import PythranSyntaxError


##
class LocalDeclarations(NodeAnalysis):
    """Gathers all local symbols from a function"""
    def __init__(self):
        self.result = set()
        super(LocalDeclarations, self).__init__()

    def visit_Assign(self, node):
        for t in node.targets:
            assert isinstance(t, ast.Name) or isinstance(t, ast.Subscript)
            if isinstance(t, ast.Name) and not md.get(t, md.LocalVariable):
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
    """Statically compute the value of locals() before each statement"""
    def __init__(self):
        self.result = dict()
        self.locals = set()
        super(Locals, self).__init__(GlobalDeclarations)

    def generic_visit(self, node):
        ModuleAnalysis.generic_visit(self, node)
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
        if node.name not in self.global_declarations:
            self.locals.add(node.name)
        self.expr_parent = node
        self.result[node] = self.locals.copy()
        parent_locals = self.locals.copy()
        self.locals.update(arg.id for arg in node.args.args)
        map(self.visit, node.body)
        self.locals = parent_locals

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
                + builtin_constants.keys()
                + builtin_constructors.keys()
                + ['__builtin__'])


##
class ImportedIds(NodeAnalysis):
    """Gather ids referenced by a node and not declared locally"""
    def __init__(self):
        self.result = set()
        self.current_locals = set()
        super(ImportedIds, self).__init__(Globals, Locals)

    def visit_Name(self, node):
        if isinstance(node.ctx, ast.Store):
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
        self.visible_globals = set(self.globals) - self.locals[node]

    def run(self, node, ctx):
        if isinstance(node, list):  # so that this pass can be called on list
            node = ast.If(ast.Num(1), node, None)
        return super(ImportedIds, self).run(node, ctx)


##
class ConstantExpressions(NodeAnalysis):
    """Identify constant expressions (dummy implementation)"""
    def __init__(self):
        self.result = set()
        NodeAnalysis.__init__(self, Globals, Locals, PureFunctions, Aliases)

    def add(self, node):
        self.result.add(node)
        return True

    def visit_BoolOp(self, node):
        return all(self.visit(n) for n in node.values) and self.add(node)

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
        return rec(modules, node).isconst()

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
                if isinstance(alias, ast.Call):  # this is a bind
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
        values = values or set()
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
        return self.add(node,
                self.visit(node.body).union(self.visit(node.orelse)))

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
                    functions.get(func.attr, [(None, None)])[0])
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
        if isinstance(f, ast.Attribute) and f.attr.startswith("bind"):
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
        self.aliases.update((k, {k})
            for k, v in builtin_constants.iteritems())
        self.aliases.update((k, {v})
            for k, v in builtin_constructors.iteritems())
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
        self.generic_visit(node)

    def visit_If(self, node):
        self.visit(node.test)
        false_aliases = self.aliases.copy()
        map(self.visit, node.body)
        true_aliases, self.aliases = self.aliases, false_aliases
        map(self.visit, node.orelse)
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

    def visit_alias(self, node):
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
        for n in builtin_constructors.itervalues():
            fe = ArgumentEffects.ConstructorEffects(n)
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
        map(register_node, builtin_constructors.itervalues())
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
        func_aliases = self.aliases[node].state[Aliases.access_path(node.func)]
        # expand argument if any
        func_aliases = reduce(
                lambda x, y: x
                    + (self.all_functions if isinstance(y, ast.Name) else [y]),
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
        for n in builtin_constructors.itervalues():
            fe = ArgumentReadOnce.ConstructorEffects(n)
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
