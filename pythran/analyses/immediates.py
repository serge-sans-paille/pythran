""" Immediates gathers immediates. For now, only integers within shape are
considered as immediates """

import gast as ast
from pythran.tables import MODULES
from pythran.analyses import Aliases
from pythran.passmanager import NodeAnalysis
from pythran.utils import pythran_builtin, isnum

_make_shape = pythran_builtin('make_shape')


class Immediates(NodeAnalysis):
    def __init__(self):
        self.result = set()
        super(Immediates, self).__init__(Aliases)

    def visit_Call(self, node):
        func_aliases = self.aliases[node.func]
        for alias in func_aliases:
            if getattr(alias, "immediate_arguments", []):
                for i, arg in enumerate(node.args):
                    if i in alias.immediate_arguments:
                        if isinstance(arg, ast.Constant):
                            self.result.add(arg)

        if len(func_aliases) == 1 and next(iter(func_aliases)) is _make_shape:
            self.result.update(a for a in node.args
                               if isnum(a)
                               and isinstance(a.value, int)
                               and a.value >= 0)
            return

        return self.generic_visit(node)
