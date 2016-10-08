"""IterTransformation replaces expressions by iterators when possible."""

from pythran.analyses import PotentialIterator, Aliases
from pythran.passmanager import Transformation
from pythran.tables import MODULES
from pythran.utils import path_to_attr

import gast as ast
import sys

EQUIVALENT_ITERATORS = {}

if sys.version_info.major == 2:

    EQUIVALENT_ITERATORS.update({
        "range": ("__builtin__", "xrange"),
        "filter": ("itertools", "ifilter"),
        "map": ("itertools", "imap"),
        "zip": ("itertools", "izip")
    })


class IterTransformation(Transformation):

    """
    Replaces expressions by iterators when possible.

    >>> import gast as ast
    >>> from pythran import passmanager, backend
    >>> node = ast.parse('''
    ... def foo(l):
    ...     return __builtin__.sum(l)
    ... def bar(n):
    ...     return foo(__builtin__.range(n))
    ... ''')
    >>> pm = passmanager.PassManager("test")
    >>> _, node = pm.apply(IterTransformation, node)
    >>> print pm.dump(backend.Python, node)
    import itertools
    def foo(l):
        return __builtin__.sum(l)
    def bar(n):
        return foo(__builtin__.xrange(n))
    """

    def __init__(self):
        """Gather required information."""
        Transformation.__init__(self, PotentialIterator, Aliases)

    def find_matching_builtin(self, node):
        """
        Return matched keyword.

        If the node alias on a correct keyword (and only it), it matchs.
        """
        for keyword in EQUIVALENT_ITERATORS.keys():
            correct_alias = set([MODULES["__builtin__"][keyword]])
            if self.aliases[node.func] == correct_alias:
                return keyword

    def visit_Module(self, node):
        """Add itertools import for imap, izip or ifilter iterator."""
        self.generic_visit(node)
        importIt = ast.Import(names=[ast.alias(name='itertools', asname=None)])
        return ast.Module(body=([importIt] + node.body))

    def visit_Call(self, node):
        """Replace function call by its correct iterator if it is possible."""
        if node in self.potential_iterator:
            match_keyword = self.find_matching_builtin(node)
            # Special handling for map which can't be turn to imap with None as
            # a parameter as map(None, [1, 2]) == [1, 2] while
            # list(imap(None, [1, 2])) == [(1,), (2,)]
            if match_keyword == "map":
                if MODULES["__builtin__"]["None"] in self.aliases[node.args[0]]:
                    return self.generic_visit(node)
            if match_keyword:
                node.func = path_to_attr(EQUIVALENT_ITERATORS[match_keyword])
                self.update = True
        return self.generic_visit(node)
