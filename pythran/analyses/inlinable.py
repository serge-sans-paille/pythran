""" Inlinable list function that may be inlined. """

from pythran.passmanager import ModuleAnalysis
from pythran.analyses import Identifiers
from pythran.analyses.pure_expressions import PureExpressions
import pythran.metadata as metadata

import gast as ast
import copy


class Inlinable(ModuleAnalysis):

    """ Determine set of inlinable function.

    A function can be inlined if it has only one statement and doesn't
    recurse on itself.
    """

    def __init__(self):
        self.result = dict()
        super(Inlinable, self).__init__(PureExpressions)

    def visit_FunctionDef(self, node):
        """ Determine this function definition can be inlined. """
        if len(node.body) != 1:
            return

        sbody = node.body[0]
        if not isinstance(sbody, (ast.Call, ast.Return)):
            return

        # only consider static return if they are pure
        if metadata.get(sbody, metadata.StaticReturn):
            if sbody not in self.pure_expressions:
                return

        ids = self.gather(Identifiers, sbody)
        # FIXME : It mark "not inlinable" def foo(foo): return foo
        if node.name not in ids:
            self.result[node.name] = copy.deepcopy(node)
