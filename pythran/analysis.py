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
'''

from tables import modules, builtin_constants, builtin_constructors
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
        NodeAnalysis.__init__(self)

    def visit_Assign(self, node):
        for t in node.targets:
            assert isinstance(t, ast.Name) or isinstance(t, ast.Subscript)
            if isinstance(t, ast.Name) and not md.get(t, md.LocalVariable):
                self.result.add(t)

    def visit_For(self, node):
        assert isinstance(node.target, ast.Name)
        self.result.add(node.target)
        [self.visit(n) for n in node.body]


##
class GlobalDeclarations(ModuleAnalysis):
    """Generates a function name -> function node binding"""
    def __init__(self):
        self.result = dict()
        ModuleAnalysis.__init__(self)

    def visit_Import(self, node):
        for alias in node.names:
            self.result[alias.name] = alias

    def visit_ImportFrom(self, node):
        for alias in node.names:
            self.result[alias.asname or alias.name] = alias
        return None

    def visit_FunctionDef(self, node):
        self.result[node.name] = node


##
class Locals(ModuleAnalysis):
    """Statically compute the value of locals() before each statement"""
    def __init__(self):
        self.result = dict()
        self.locals = set()
        ModuleAnalysis.__init__(self, GlobalDeclarations)

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
        [self.visit(n) for n in node.body]

    def visit_FunctionDef(self, node):
        self.expr_parent = node
        self.result[node] = self.locals.copy()
        parent_locals = self.locals.copy()
        self.locals.update(arg.id for arg in node.args.args)
        [self.visit(n) for n in node.body]
        self.locals = parent_locals

    def visit_Assign(self, node):
        self.expr_parent = node
        self.result[node] = self.locals.copy()
        self.visit(node.value)
        self.locals.update(t.id for t in node.targets
                if isinstance(t, ast.Name))

    def visit_For(self, node):
        self.expr_parent = node
        self.result[node] = self.locals.copy()
        self.visit(node.iter)
        self.locals.add(node.target.id)
        [self.visit(n) for n in node.body]
        [self.visit(n) for n in node.orelse]

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
        [self.visit(n) for n in node.body]

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
        self.result = dict()
        ModuleAnalysis.__init__(self, GlobalDeclarations)

    def visit(self, node):
        pass

    def run(self, node, ctx):
        ModuleAnalysis.run(self, node, ctx)
        return set(self.global_declarations.keys()
                + modules["__builtins__"].keys()
                + builtin_constants.keys()
                + builtin_constructors.keys())


##
class ImportedIds(NodeAnalysis):
    """Gather ids referenced by a node and not declared locally"""
    def __init__(self):
        self.result = set()
        self.current_locals = set()
        NodeAnalysis.__init__(self, Globals, Locals)

    def visit_Name(self, node):
        if isinstance(node.ctx, ast.Store):
            self.current_locals.add(node.id)
        elif (node.id not in self.visible_globals
                and node.id not in self.current_locals):
            self.result.add(node.id)

    def visit_FunctionDef(self, node):
        self.current_locals.add(node.name)
        result = self.result.copy()
        current_locals = self.current_locals.copy()
        self.current_locals.update(arg.id for arg in node.args.args)
        [self.visit(n) for n in node.body]
        self.current_locals = current_locals

    def visit_AnyComp(self, node):
        current_locals = self.current_locals.copy()
        [self.visit(n) for n in node.generators]
        self.visit(node.elt)
        self.current_locals = current_locals

    def visit_ListComp(self, node):
        self.visit_AnyComp(node)

    def visit_SetComp(self, node):
        self.visit_AnyComp(node)

    def visit_GeneratorExp(self, node):
        self.visit_AnyComp(node)

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

    def run(self, node, ctx):
        if isinstance(node, list):
            node = ast.If(ast.Num(1), node, None)
        return NodeAnalysis.run(self, node, ctx)

    def run_visit(self, node):
        self.visible_globals = set(self.globals) - self.locals[node]
        NodeAnalysis.run_visit(self, node)


##
class ConstantExpressions(NodeAnalysis):
    """Identify constant expressions (dummy implementation)"""
    def __init__(self):
        self.result = set()
        NodeAnalysis.__init__(self, Globals, Locals)

    def add(self, node):
        self.result.add(node)
        return True

    def visit_BoolOp(self, node):
        return all(self.visit(n) for n in node.values) and self.add(node)

    def visit_BinOp(self, node):
        return (all(self.visit(n) for n in (node.left, node.right))
                and self.add(node))

    def visit_UnaryOp(self, node):
        return self.visit(node.operand) and self.add(node)

    def visit_IfExp(self, node):
        return (all(self.visit(n) for n in (node.test, node.body, node.orelse))
                and self.add(node))

    def visit_Dict(self, node):
        return (all(self.visit(n) for n in (node.keys + node.values))
                and self.add(node))

    def visit_Set(self, node):
        return all(self.visit(n) for n in node.elts) and self.add(node)

    def visit_Compare(self, node):
        return (all(self.visit(n) for n in [node.left] + node.comparators)
                and self.add(node))

    def visit_Call(self, node):
        return (all(self.visit(n) for n in node.args + [node.func])
                and self.add(node))

    def visit_Num(self, node):
        return self.add(node)

    def visit_Str(self, node):
        return self.add(node)

    def visit_Subscript(self, node):
        return (all(self.visit(n) for n in (node.value, node.slice))
                and self.add(node))

    def visit_Name(self, node):
        if node in self.locals:
            return (node.id not in self.locals[node]
                    and node.id in modules['__builtins__']
                    and modules['__builtins__'][node.id].isconst())
        else:  # not in an expression
            return False

    def visit_Attribute(self, node):
        assert isinstance(node.value, ast.Name)
        return (node.value.id in modules
                and modules[node.value.id][node.attr].isconst())

    def visit_List(self, node):
        return all([self.visit(n) for n in node.elts]) and self.add(node)

    def visit_Tuple(self, node):
        return all([self.visit(n) for n in node.elts]) and self.add(node)

    def visit_Slice(self, node):
        l = (self.visit(node.lower) if node.lower else True)
        u = (self.visit(node.upper) if node.upper else True)
        s = (self.visit(node.step) if node.step else True)
        return False

    def visit_Index(self, node):
        return self.visit(node.value) and self.add(node)


##
class OrderedGlobalDeclarations(ModuleAnalysis):
    '''Order all global functions according to their callgraph depth'''
    def __init__(self):
        self.result = dict()
        ModuleAnalysis.__init__(self, Aliases, GlobalDeclarations)

    def visit_FunctionDef(self, node):
        self.curr = node
        self.result[node] = set()
        [self.visit(n) for n in node.body]

    def visit_Name(self, node):
        if (node.id in self.global_declarations
                and isinstance(
                    self.global_declarations[node.id],
                    ast.FunctionDef)):
            self.result[self.curr].add(self.global_declarations[node.id])

        elif node in self.aliases:
            for alias in self.aliases[node].aliases:
                if (alias in self.global_declarations
                        and isinstance(alias, ast.FunctionDef)):
                    self.result[self.curr].add(self.global_declarations[alias])

    def run(self, node, ctx):
        ModuleAnalysis.run(self, node, ctx)
        old_count = -1
        new_count = 0
        while new_count != old_count:
            for k, v in self.result.iteritems():
                for f in list(v):
                    v.update(self.result[f])
            old_count = new_count
            new_count = reduce(
                    lambda acc, s: acc + len(s),
                    self.result.itervalues(),
                    0)
        return sorted(
                self.result.iterkeys(),
                key=lambda s: len(self.result[s]),
                reverse=True)


##
class Aliases(ModuleAnalysis):
    """Gather aliasing informations across nodes."""
    class AliasingInformation(object):
        def __init__(self, state, aliases):
            self.state = state
            self.aliases = aliases

    def __init__(self):
        self.result = dict()
        self.aliases = dict()
        ModuleAnalysis.__init__(self, GlobalDeclarations)

    @staticmethod
    def access_path(node):
        if isinstance(node, ast.Name):
            return (node.id,)
        elif isinstance(node, ast.Attribute):
            return Aliases.access_path(node.value) + (node.attr,)
        else:
            raise NotImplementedError

    # aliasing created by expressions
    def add(self, node, values=None):
        values = values or set()
        assert isinstance(values, set)
        self.result[node] = Aliases.AliasingInformation(
                self.aliases.copy(),
                values)
        return values

    def visit_OMPDirective(self, node):
        pass

    def visit_BoolOp(self, node):
        return self.add(node,
                reduce(set.union, (self.visit(n) for n in node.values), set()))

    def visit_BinOp(self, node):
        self.generic_visit(node)
        return self.add(node)

    def visit_UnaryOp(self, node):
        self.generic_visit(node)
        return self.add(node)

    def visit_IfExp(self, node):
        return self.add(node,
                self.visit(node.body).union(self.visit(node.orelse)))

    def visit_Dict(self, node):
        self.generic_visit(node)
        return self.add(node)  # not very accurate

    def visit_Set(self, node):
        self.generic_visit(node)
        return self.add(node)  # not very accurate

    def visit_Compare(self, node):
        self.generic_visit(node)
        return self.add(node)

    def visit_Call(self, node):
        self.visit(node.func)
        if isinstance(node.func, ast.Name) and node.func.id.startswith("bind"):
            [self.visit(n) for n in node.args]
            return self.add(node, {node})
        else:
            return self.add(node,
                    reduce(
                        set.union,
                        (self.visit(n) for n in node.args),
                        set(self.global_declarations.itervalues())
                        )
                    )  # should include built-ins too

    def visit_Num(self, node):
        return self.add(node)

    def visit_Str(self, node):
        return self.add(node)

    def visit_Attribute(self, node):
        return self.add(node, {node})

    def visit_Subscript(self, node):
        self.generic_visit(node)
        # not very accurate, could be enhanced through better handling of sets
        return self.add(node)

    def visit_Name(self, node):
        if (node.id,) not in self.aliases:
            err = ("identifier {0} unknown, either because",
                    "it is an unsupported intrinsic,"
                    "the input code is faulty,"
                    "or... pythran is buggy.")
            raise PythranSyntaxError("\n".join(err).format(node.id), node)
        return self.add(node, self.aliases[(node.id,)].copy())

    def visit_List(self, node):
        self.generic_visit(node)
        return self.add(node)  # not very accurate

    def visit_Tuple(self, node):
        self.generic_visit(node)
        return self.add(node)  # not very accurate

    # aliasing created by statements

    def visit_FunctionDef(self, node):
        self.aliases = dict()
        self.aliases.update({(k,): {v}
            for k, v in builtin_constants.iteritems()})
        self.aliases.update({(k,): {v}
            for k, v in builtin_constructors.iteritems()})
        for module in modules:
            self.aliases.update({
                (k,) if module == "__builtins__" else (module, k): {v}
                for k, v in modules[module].iteritems()})
        self.aliases.update({(f.name,): {f}
            for f in self.global_declarations.itervalues()})
        self.aliases.update({(arg.id,): {arg}
            for arg in node.args.args})
        self.generic_visit(node)

    def visit_Assign(self, node):
        value_aliases = self.visit(node.value)
        for t in node.targets:
            if isinstance(t, ast.Name):
                self.aliases[(t.id,)] = value_aliases or {t}
            else:
                self.visit(t)

    def visit_For(self, node):
        self.aliases[(node.target.id,)] = {node.target}
        self.generic_visit(node)

    def visit_If(self, node):
        self.visit(node.test)
        false_aliases = self.aliases.copy()
        [self.visit(n) for n in node.body]
        true_aliases, self.aliases = self.aliases, false_aliases
        [self.visit(n) for n in node.orelse]
        for k, v in true_aliases.iteritems():
            if k in self.aliases:
                self.aliases[k].update(v)
            else:
                assert isinstance(v, set)
                self.aliases[k] = v

    def visit_ExceptHandler(self, node):
        if node.name:
            self.aliases[(node.name.id,)] = {node.name}
            self.generic_visit(node)


##
class Identifiers(NodeAnalysis):
    """Gather all identifiers used throughout a node."""
    def __init__(self):
        self.result = set()
        NodeAnalysis.__init__(self)

    def visit_Name(self, node):
        self.result.add(node.id)

    def visit_FunctionDef(self, node):
        self.result.add(node.name)
        self.visit(node.args)
        [self.visit(n) for n in node.body]

    def visit_alias(self, node):
        if node.asname:
            self.result.add(node.asname)


##
class YieldPoints(FunctionAnalysis):
    '''Gathers all yield points of a generator, if any.'''
    def __init__(self):
        self.result = list()
        FunctionAnalysis.__init__(self)

    def visit_Yield(self, node):
        self.result.append(node)


##
class BoundedExpressions(ModuleAnalysis):
    '''Gathers all nodes that are bound to an identifier.'''
    def __init__(self):
        self.result = set()
        ModuleAnalysis.__init__(self)

    def visit_Assign(self, node):
        self.result.add(node.value)
        if isinstance(node.value, ast.Subscript):
            self.result.add(node.value.slice)
        self.visit(node.value)
        [self.visit(n) for n in node.targets]

    def visit_Call(self, node):
        for n in node.args:
            if isinstance(n, ast.Subscript):
                self.result.add(n)

    def visit_Return(self, node):
        self.visit(node.value)
        if node.value:
            self.result.add(node.value)
            if isinstance(node.value, ast.Subscript):
                self.result.add(node.value.slice)


##
class UpdateEffects(ModuleAnalysis):
    '''Gathers inter-procedural update effects of functions.'''
    class FunctionEffects(object):
        def __init__(self, node):
            self.func = node
            if isinstance(node, ast.FunctionDef):
                self.update_effects = [False] * len(node.args.args)
            elif isinstance(node, intrinsic.Intrinsic):
                self.update_effects = [isinstance(x, intrinsic.UpdateEffect)
                        for x in node.effects]
            elif isinstance(node, ast.alias):
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
        ModuleAnalysis.__init__(self, Aliases, GlobalDeclarations)

    def run_visit(self, node):
        for n in self.global_declarations.itervalues():
            fe = UpdateEffects.FunctionEffects(n)
            self.node_to_functioneffect[n] = fe
            self.result.add_node(fe)
        for n in builtin_constructors.itervalues():
            fe = UpdateEffects.ConstructorEffects(n)
            self.node_to_functioneffect[n] = fe
            self.result.add_node(fe)
        for m in modules:
            for name, intrinsic in modules[m].iteritems():
                fe = UpdateEffects.FunctionEffects(intrinsic)
                self.node_to_functioneffect[intrinsic] = fe
                self.result.add_node(fe)
        self.all_functions = [fe.func for fe in self.result]
        return ModuleAnalysis.run_visit(self, node)

    def run(self, node, ctx):
        ModuleAnalysis.run(self, node, ctx)
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
