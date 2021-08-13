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
                keepdims = node.args[4]
                if isinstance(keepdims, ast.Constant):
                    self.result.add(keepdims)

        if len(func_aliases) == 1 and next(iter(func_aliases)) is MODULES['numpy']['unique']:
            if len(node.args) >= 2:
                return_index = node.args[1]
                if isinstance(return_index, ast.Constant):
                    self.result.add(return_index)
            if len(node.args) >= 3:
                return_inverse = node.args[2]
                if isinstance(return_inverse, ast.Constant):    
                    self.result.add(return_inverse)
            if len(node.args) >= 4:
                return_counts = node.args[3]
                if isinstance(return_counts, ast.Constant): 
                    self.result.add(return_counts)

        if len(func_aliases) == 1 and next(iter(func_aliases)) is _make_shape:
            self.result.update(a for a in node.args
                               if isnum(a)
                               and isinstance(a.value, int)
                               and a.value >= 0)
            return

        return self.generic_visit(node)
