""" Expand some builtins implementation when it is profitable."""

from pythran.analyses import Aliases
from pythran.analyses.pure_expressions import PureExpressions
from pythran.passmanager import Transformation
from pythran.tables import MODULES
from pythran.intrinsic import FunctionIntr

import gast as ast
import sys


class InlineBuiltins(Transformation):

    """
    Replace some builtins by their bodies.

    This may trigger some extra optimizations later on!

    >>> import gast as ast
    >>> from pythran import passmanager, backend
    >>> pm = passmanager.PassManager("test")
    >>> node = ast.parse('''
    ... def foo(a):
    ...     return  a + 1
    ... def bar(b):
    ...     return __builtin__.map(bar, (1, 2))''')
    >>> _, node = pm.apply(InlineBuiltins, node)
    >>> print(pm.dump(backend.Python, node))
    def foo(a):
        return (a + 1)
    def bar(b):
        return [bar(1), bar(2)]
    """

    def __init__(self):
        Transformation.__init__(self, Aliases, PureExpressions)

    def inlineBuiltinsXMap(self, node):
        self.update = True

        elts = []
        nelts = min(len(n.elts) for n in node.args[1:])
        for i in range(nelts):
            elts.append([n.elts[i] for n in node.args[1:]])
        return ast.List([ast.Call(node.args[0], elt, []) for elt in elts],
                        ast.Load())

    def inlineBuiltinsIMap(self, node):

        if not isinstance(node, ast.Call):
            return node

        func_aliases = self.aliases[node.func]
        if len(func_aliases) != 1:
            return node

        obj = next(iter(func_aliases))
        if obj is not MODULES['itertools']['imap']:
            return node

        if not all(isinstance(arg, (ast.List, ast.Tuple))
                   for arg in node.args[1:]):
            return node

        mapped_func_aliases = self.aliases[node.args[0]]
        if len(mapped_func_aliases) != 1:
            return node

        obj = next(iter(mapped_func_aliases))
        if not isinstance(obj, (ast.FunctionDef, FunctionIntr)):
            return node

        if isinstance(obj, FunctionIntr) and not obj.isconst():
            return node  # inlining as a list would force evaluation
        if obj not in self.pure_expressions:
            return node  # inlining as a list would force evaluation

        # all preconditions are met, do it!
        return self.inlineBuiltinsXMap(node)

    def inlineBuiltinsMap(self, node):

        if not isinstance(node, ast.Call):
            return node

        func_aliases = self.aliases[node.func]
        if len(func_aliases) != 1:
            return node

        obj = next(iter(func_aliases))
        if obj is not MODULES['__builtin__']['map']:
            return node

        if not all(isinstance(arg, (ast.List, ast.Tuple))
                   for arg in node.args[1:]):
            return node

        mapped_func_aliases = self.aliases[node.args[0]]
        if len(mapped_func_aliases) != 1:
            return node

        obj = next(iter(mapped_func_aliases))
        if not isinstance(obj, (ast.FunctionDef, FunctionIntr)):
            return node

        # all preconditions are met, do it!
        return self.inlineBuiltinsXMap(node)

    def visit_Call(self, node):
        node = self.generic_visit(node)
        node = self.inlineBuiltinsMap(node)
        if sys.version_info.major == 2:
            node = self.inlineBuiltinsIMap(node)
        return node
