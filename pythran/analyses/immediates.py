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
        if len(func_aliases) == 1 and next(iter(func_aliases)) is MODULES['numpy']['mean']:
            if len(node.args) >= 5:
                keep_dims = node.args[4]
                if isinstance(keep_dims, ast.Constant):
                    self.result.add(keep_dims)

        if len(func_aliases) == 1 and next(iter(func_aliases)) is _make_shape:
            self.result.update(a for a in node.args
                               if isnum(a)
                               and isinstance(a.value, int)
                               and a.value >= 0)
            return

        return self.generic_visit(node)
