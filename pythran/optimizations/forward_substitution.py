"""
Replace variable that can be lazy evaluated and used only once by their full
computation code.
"""

from pythran.analyses import LazynessAnalysis, UseDefChains, DefUseChains
from pythran.analyses import Literals, Ancestors
from pythran.passmanager import Transformation

import gast as ast

try:
    from math import isfinite
except ImportError:
    from math import isinf, isnan
    isfinite = lambda x: not isinf(x) and not isnan(x)


class Remover(ast.NodeTransformer):

    def __init__(self, nodes):
        self.nodes = nodes

    def generic_visit(self, node):
        if node in self.nodes:
            return ast.Pass()
        return super(Remover, self).generic_visit(node)


class ForwardSubstitution(Transformation):

    """
    Replace variable that can be computed later.

    >>> import gast as ast
    >>> from pythran import passmanager, backend
    >>> pm = passmanager.PassManager("test")
    >>> node = ast.parse("from __future__ import print_function\\n\
def foo(): a = [2, 3]; __builtin__.print(a)")
    >>> _, node = pm.apply(ForwardSubstitution, node)
    >>> print(pm.dump(backend.Python, node))
    from __future__ import print_function
    def foo():
        pass
        __builtin__.print([2, 3])
    >>> node = ast.parse("from __future__ import print_function\\n\
def foo(): a = 2; __builtin__.print(a + a)")
    >>> _, node = pm.apply(ForwardSubstitution, node)
    >>> print(pm.dump(backend.Python, node))
    from __future__ import print_function
    def foo():
        a = 2
        __builtin__.print((2 + 2))
    """

    def __init__(self):
        """ Satisfy dependencies on others analyses. """
        super(ForwardSubstitution, self).__init__(LazynessAnalysis,
                                                  UseDefChains,
                                                  DefUseChains,
                                                  Ancestors,
                                                  Literals)
        self.to_remove = set()

    def visit_FunctionDef(self, node):
        self.to_remove = set()
        self.locals = self.def_use_chains.locals[node]

        # prune some assignment as a second phase, as an assignment could be
        # forward-substituted several times (in the case of constants)
        self.generic_visit(node)
        Remover(self.to_remove).visit(node)
        return node

    def visit_Name(self, node):
        if not isinstance(node.ctx, ast.Load):
            return node

        # OpenMP metdata are not handled by beniget, which is fine in our case
        if node not in self.use_def_chains:
            if __debug__:
                from pythran.openmp import OMPDirective
                assert any(isinstance(p, OMPDirective)
                           for p in self.ancestors[node])
            return node
        defuses = self.use_def_chains[node]

        if len(defuses) != 1:
            return node

        defuse = defuses[0]

        dnode = defuse.node
        if not isinstance(dnode, ast.Name):
            return node

        # multiple definition, which one should we forward?
        if sum(1 for d in self.locals if d.name() == dnode.id) > 1:
            return node

        # either a constant or a value
        fwd = (dnode in self.literals and
               isfinite(self.lazyness_analysis[dnode.id]))
        fwd |= self.lazyness_analysis[dnode.id] == 1

        if not fwd:
            return node

        parent = self.ancestors[dnode][-1]
        if isinstance(parent, ast.Assign):
            value = parent.value
            if dnode in self.literals:
                self.update = True
                if len(defuse.users()) == 1:
                    self.to_remove.add(parent)
                    return value
                else:
                    # FIXME: deepcopy here creates an unknown node
                    # for alias computations
                    return value
            elif len(parent.targets) == 1:
                self.update = True
                self.to_remove.add(parent)
                return value

        return node
