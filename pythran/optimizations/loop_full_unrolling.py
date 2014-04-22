"""
LoopFullUnrolling fully unrolls loops with static bounds
"""
import ast
from copy import deepcopy
from pythran import metadata
from pythran.analyses import HasBreak, HasContinue, NodeCount
from pythran.openmp import OMPDirective
from pythran.passmanager import Transformation


class LoopFullUnrolling(Transformation):
    '''
    Fully unroll loops with static bounds

    >>> import ast, passmanager, backend
    >>> node = ast.parse('for j in [1,2,3]: i += j')
    >>> pm = passmanager.PassManager("test")
    >>> node = pm.apply(LoopFullUnrolling, node)
    >>> print pm.dump(backend.Python, node)
    j = 1
    i += j
    j = 2
    i += j
    j = 3
    i += j
    '''

    MAX_NODE_COUNT = 512

    def visit_For(self, node):
        # first unroll children if needed or possible
        self.generic_visit(node)

        # if the user added some OpenMP directive, trust him and no unroll
        has_omp = metadata.get(node, OMPDirective)
        # a break or continue in the loop prevents unrolling too
        has_break = any(self.passmanager.gather(HasBreak, n, self.ctx)
                        for n in node.body)
        has_cont = any(self.passmanager.gather(HasContinue, n, self.ctx)
                       for n in node.body)
        # do not unroll too much to prevent code growth
        node_count = self.passmanager.gather(NodeCount, node, self.ctx)

        if type(node.iter) is ast.List:
            isvalid = not(has_omp or has_break or has_cont)
            total_count = node_count * len(node.iter.elts)
            issmall = total_count < LoopFullUnrolling.MAX_NODE_COUNT
            if isvalid and issmall:
                def unroll(elt):
                    return ([ast.Assign([deepcopy(node.target)], elt)]
                            + deepcopy(node.body))
                return reduce(list.__add__, map(unroll, node.iter.elts))
        return node
