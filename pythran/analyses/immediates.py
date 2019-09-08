""" Immediates gathers immediates. For now, only integers within shape are
considered as immediates """

from pythran.analyses import Aliases
from pythran.passmanager import NodeAnalysis
from pythran.utils import pythran_builtin, isnum

import gast as ast

_make_shape = pythran_builtin('make_shape')


class Immediates(NodeAnalysis):
    def __init__(self):
        self.result = set()
        super(Immediates, self).__init__(Aliases)

    def visit_Call(self, node):
        func_aliases = self.aliases[node.func]
        if len(func_aliases) == 1 and next(iter(func_aliases)) is _make_shape:
            self.result.update(a for a in node.args
                               if isnum(a)
                               and isinstance(a.value, int)
                               and a.value >= 0)
            return

        return self.generic_visit(node)
