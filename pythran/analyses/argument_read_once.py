"""
ArgumentReadOnce counts the usages of each argument of each function
"""
import ast
from aliases import Aliases
from global_declarations import GlobalDeclarations
import networkx as nx
import pythran.intrinsic as intrinsic
from pythran.passmanager import ModuleAnalysis
from pythran.tables import modules


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
