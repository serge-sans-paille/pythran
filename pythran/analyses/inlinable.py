""" Inlinable list function that may be inlined. """

from pythran.passmanager import ModuleAnalysis
from pythran.analyses import Identifiers

import ast
import copy


class Inlinable(ModuleAnalysis):

    """ Determine set of inlinable function.

    A function can be inlined if it has only one statement and doesn't
    recurse on itself.
    """

    def __init__(self):
        self.result = dict()
        super(Inlinable, self).__init__()

    def visit_FunctionDef(self, node):
        """ Determine this function definition can be inlined. """
        if (len(node.body) == 1 and
                isinstance(node.body[0], (ast.Call, ast.Return))):
            ids = self.passmanager.gather(Identifiers, node.body[0], self.ctx)
            # FIXME : It mark "not inlinable" def foo(foo): return foo
            if node.name not in ids:
                self.result[node.name] = copy.deepcopy(node)
