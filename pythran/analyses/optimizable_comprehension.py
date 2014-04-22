"""
OptimizableComp finds whether a comprehension can be optimized.
"""
import ast
from pythran.passmanager import NodeAnalysis
from identifiers import Identifiers


class OptimizableComprehension(NodeAnalysis):
    """Find whether a comprehension can be optimized."""
    def __init__(self):
        self.result = set()
        super(OptimizableComprehension, self).__init__(Identifiers)

    def check_comprehension(self, iters):
        targets = {gen.target.id for gen in iters}
        optimizable = True

        for it in iters:
            ids = self.passmanager.gather(Identifiers, it, self.ctx)
            optimizable &= all(((ident == it.target.id)
                                | (ident not in targets)) for ident in ids)

        return optimizable

    def visit_ListComp(self, node):
        if (self.check_comprehension(node.generators)):
            self.result.add(node)

    def visit_GeneratorExp(self, node):
        if (self.check_comprehension(node.generators)):
            self.result.add(node)
