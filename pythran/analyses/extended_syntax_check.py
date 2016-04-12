"""
ExtendedSyntaxCheck performs various syntax checks on the pythran AST.
"""

from pythran.passmanager import ModuleAnalysis
from pythran.analyses import StrictAliases
from pythran.syntax import PythranSyntaxError

import ast


class ExtendedSyntaxCheck(ModuleAnalysis):
    """
    Perform advanced syntax checking, based on strict aliases analysis:
    - is there a function redefinition?
    - is there a function call that does not match the called expression arity?
    """

    def __init__(self):
        self.result = None
        self.update = False
        self.functions = set()
        ModuleAnalysis.__init__(self, StrictAliases)

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
        for alias in self.strict_aliases[func]:
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
