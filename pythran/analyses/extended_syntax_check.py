"""
ExtendedSyntaxCheck performs various syntax checks on the pythran AST.
"""

from pythran.passmanager import ModuleAnalysis
from pythran.analyses import StrictAliases, ArgumentEffects
from pythran.syntax import PythranSyntaxError
from pythran import metadata

import gast as ast


class ExtendedSyntaxCheck(ModuleAnalysis):
    """
    Perform advanced syntax checking, based on strict aliases analysis:
    - is there a function redefinition?
    - is there a function call that does not match the called expression arity?
    - is there an operation that updates a global variable?
    """

    def __init__(self):
        self.result = None
        self.update = False
        self.functions = set()
        ModuleAnalysis.__init__(self, StrictAliases, ArgumentEffects)

    def check_global(self, node, arg):
        if not isinstance(arg, ast.Call):
            return
        try:
            aliases = self.strict_aliases[arg.func]
        except KeyError:
            return

        for alias in aliases:
            if not isinstance(alias, ast.FunctionDef):
                continue
            if metadata.get(alias.body[0], metadata.StaticReturn):
                raise PythranSyntaxError(
                    ("Cannot modify '{}': global variables are constant "
                     "in pythran.").format(alias.name),
                    node)

    def visit_FunctionDef(self, node):
        if node.name in self.functions:
            raise PythranSyntaxError("Function {} redefined".format(
                node.name),
                node)
        else:
            self.functions.add(node.name)
        self.generic_visit(node)

    def visit_Call(self, node):
        self.generic_visit(node)
        func = node.func
        try:
            aliases = self.strict_aliases[func]
        except KeyError:
            raise PythranSyntaxError(
                "Call to unknown function `{}`, it's a trap!"
                .format(getattr(func, 'id', None) or func),
                node)

        argument_effects = set()

        for alias in aliases:
            # look for effect on arguments to prepare check on globals
            try:
                func_aes = self.argument_effects[alias]
                for i, effect in enumerate(func_aes):
                    if effect:
                        argument_effects.add(i)
            except KeyError:
                pass

            if not isinstance(alias, ast.FunctionDef):
                continue
            ubound = len(alias.args.args)
            lbound = ubound - len(alias.args.defaults)
            call_args_count = len(node.args) + len(node.keywords)
            if lbound <= call_args_count <= ubound:
                continue

            if lbound == ubound:
                msg = 'Invalid call to {}: expected {} arguments, got {}'
                msg = msg.format(alias.name,
                                 len(alias.args.args),
                                 len(node.args)
                                 )
            else:
                msg = ('Invalid {} call: '
                       'expected between {} and {} arguments, got {}')
                msg = msg.format(alias.name,
                                 lbound, ubound,
                                 len(node.args)
                                 )
            raise PythranSyntaxError(msg, node)

        # check for effects on globals
        for i, arg in enumerate(node.args):
            if i not in argument_effects:
                continue
            self.check_global(node, arg)
