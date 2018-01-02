""" LoopFullUnrolling fully unrolls loops with static bounds. """

from pythran import metadata
from pythran.analyses import HasBreak, HasContinue, NodeCount
from pythran.openmp import OMPDirective
from pythran.conversion import to_ast
from pythran.passmanager import Transformation

from copy import deepcopy
import gast as ast


class LoopFullUnrolling(Transformation):
    '''
    Fully unroll loops with static bounds

    >>> import gast as ast
    >>> from pythran import passmanager, backend
    >>> node = ast.parse('for j in [1,2,3]: i += j')
    >>> pm = passmanager.PassManager("test")
    >>> _, node = pm.apply(LoopFullUnrolling, node)
    >>> print(pm.dump(backend.Python, node))
    j = 1
    i += j
    j = 2
    i += j
    j = 3
    i += j

    >>> node = ast.parse('for j in (a,b): i += j')
    >>> pm = passmanager.PassManager("test")
    >>> _, node = pm.apply(LoopFullUnrolling, node)
    >>> print(pm.dump(backend.Python, node))
    j = a
    i += j
    j = b
    i += j

    >>> node = ast.parse('for j in {1}: i += j')
    >>> pm = passmanager.PassManager("test")
    >>> _, node = pm.apply(LoopFullUnrolling, node)
    >>> print(pm.dump(backend.Python, node))
    j = 1
    i += j

    >>> node = ast.parse('for j in __builtin__.enumerate("1"): j')
    >>> pm = passmanager.PassManager("test")
    >>> _, node = pm.apply(LoopFullUnrolling, node)
    >>> print(pm.dump(backend.Python, node))
    j = (0, '1')
    j
    '''

    MAX_NODE_COUNT = 4096

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

        if has_omp or has_break or has_cont:
            return node

        # do not unroll too much to prevent code growth
        node_count = self.passmanager.gather(NodeCount, node, self.ctx)

        def unroll(elt):
            return ([ast.Assign([deepcopy(node.target)], elt)] +
                    deepcopy(node.body))

        def getrange(n):
            return getattr(getattr(n, 'func', None), 'attr', None)

        if isinstance(node.iter, (ast.Tuple, ast.List)):
            total_count = node_count * len(node.iter.elts)
            issmall = total_count < LoopFullUnrolling.MAX_NODE_COUNT
            if issmall:
                self.update = True
                return sum([unroll(elt) for elt in node.iter.elts], [])
        code = compile(ast.gast_to_ast(ast.Expression(node.iter)),
                       '<loop unrolling>', 'eval')
        try:
            values = list(eval(code,
                               {'__builtin__': __import__('__builtin__')}))
        except Exception as e:
            return node

        total_count = node_count * len(values)
        issmall = total_count < LoopFullUnrolling.MAX_NODE_COUNT
        if issmall:
            try:
                new_node = sum([unroll(to_ast(elt)) for elt in values], [])
                self.update = True
                return new_node
            except Exception as e:
                return node
        return node
