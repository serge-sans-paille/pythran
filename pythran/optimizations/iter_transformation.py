"""IterTransformation replaces expressions by iterators when possible."""

from pythran.analyses import PotentialIterator, Aliases
from pythran.passmanager import Transformation
from pythran.tables import MODULES
from pythran.utils import path_to_attr, path_to_node
from pythran.conversion import mangle

import gast as ast
import sys

EQUIVALENT_ITERATORS = {
    ('__builtin__', "list"): None,
    ('numpy', "array"): None,
    ('numpy', "asarray"): None,
}

if sys.version_info.major == 2:

    EQUIVALENT_ITERATORS.update({
        ('__builtin__', "range"): ("__builtin__", "xrange"),
        ('__builtin__', "filter"): ("itertools", "ifilter"),
        ('__builtin__', "map"): ("itertools", "imap"),
        ('__builtin__', "zip"): ("itertools", "izip")
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
    >>> print(pm.dump(backend.Python, node))
    def foo(l):
        return __builtin__.sum(l)
    def bar(n):
        return foo(__builtin__.xrange(n))
    """

    if sys.version_info.major == 3:
        __doc__ = None

    def __init__(self):
        """Gather required information."""
        Transformation.__init__(self, PotentialIterator, Aliases)
        self.use_itertools = False

    def find_matching_builtin(self, node):
        """
        Return matched keyword.

        If the node alias on a correct keyword (and only it), it matches.
        """
        for path in EQUIVALENT_ITERATORS.keys():
            correct_alias = {path_to_node(path)}
            if self.aliases[node.func] == correct_alias:
                return path

    def visit_Module(self, node):
        """Add itertools import for imap, izip or ifilter iterator."""
        self.generic_visit(node)
        import_alias = ast.alias(name='itertools', asname=mangle('itertools'))
        if self.use_itertools:
            importIt = ast.Import(names=[import_alias])
            node.body.insert(0, importIt)
        return node

    def visit_Call(self, node):
        """Replace function call by its correct iterator if it is possible."""
        if node in self.potential_iterator:
            matched_path = self.find_matching_builtin(node)
            if matched_path is None:
                return self.generic_visit(node)

            # Special handling for map which can't be turn to imap with None as
            # a parameter as map(None, [1, 2]) == [1, 2] while
            # list(imap(None, [1, 2])) == [(1,), (2,)]
            if (matched_path[1] == "map" and
                    MODULES["__builtin__"]["None"] in
                    self.aliases[node.args[0]]):
                return self.generic_visit(node)

            # if a dtype conversion is implied
            if matched_path[1] in ('array', 'asarray') and len(node.args) != 1:
                return self.generic_visit(node)

            path = EQUIVALENT_ITERATORS[matched_path]
            if path:
                node.func = path_to_attr(path)
                self.use_itertools |= path[0] == 'itertools'
            else:
                node = node.args[0]

            self.update = True
        return self.generic_visit(node)
