"""
PureExpressions detects functions without side-effects.
"""
import ast
from argument_effects import ArgumentEffects
from global_effects import GlobalEffects
from aliases import Aliases
from pythran.passmanager import ModuleAnalysis


class PureExpressions(ModuleAnalysis):
    '''Yields the set of pure expressions'''
    def __init__(self):
        self.result = set()
        super(PureExpressions, self).__init__(ArgumentEffects, GlobalEffects,
                                              Aliases)

    def visit_FunctionDef(self, node):
        map(self.visit, node.body)
        # Pure functions are already compute, we don't need to add them again
        return False

    def generic_visit(self, node):
        is_pure = all(map(self.visit, ast.iter_child_nodes(node)))
        if is_pure:
            self.result.add(node)
        return is_pure

    def visit_Call(self, node):
        # check if all arguments are Pures
        is_pure = all(self.visit(arg) for arg in node.args)
        # check if all possible function used are Pures
        func_aliases = self.aliases[node.func].aliases
        is_pure &= func_aliases.issubset(self.result)
        # check for chained call
        is_pure &= self.visit(node.func)
        if is_pure:
            self.result.add(node)
        return is_pure

    def run(self, node, ctx):
        super(PureExpressions, self).prepare(node, ctx)
        no_arg_effect = set()
        for func, ae in self.argument_effects.iteritems():
            if not any(ae):
                no_arg_effect.add(func)
        self.result = no_arg_effect.difference(self.global_effects)
        self.visit(node)
        return self.result
