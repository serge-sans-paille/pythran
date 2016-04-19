"""
PureExpressions detects functions without side-effects.
"""

from pythran.analyses.aliases import Aliases
from pythran.analyses.argument_effects import ArgumentEffects
from pythran.analyses.global_effects import GlobalEffects
from pythran.passmanager import ModuleAnalysis
from pythran.intrinsic import Intrinsic

import ast


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

        # check all possible function called
        func_aliases = self.aliases[node.func]
        if func_aliases:
            for func_alias in func_aliases:
                # does the function have a global effect?
                if isinstance(func_alias, Intrinsic):
                    is_pure &= not func_alias.global_effects
                else:
                    is_pure &= func_alias in self.result

                # does the function have an argument effect ?
                # trivial arguments can be ignored
                if func_alias in self.argument_effects:
                    func_aes = self.argument_effects[func_alias]
                    for arg, ae in zip(node.args, func_aes):
                        if ae:
                            try:
                                ast.literal_eval(arg)
                            except ValueError:
                                is_pure = False
                else:
                    is_pure = False
        else:
            is_pure = False  # conservative choice

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
