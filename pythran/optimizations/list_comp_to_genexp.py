"""
ListCompToGenexp transforms list comprehension into genexp
"""
import ast
from pythran.analyses import PotentialIterator
from pythran.passmanager import Transformation
from pythran.transformations import NormalizeTuples


class ListCompToGenexp(Transformation):
    '''
    Transforms list comprehension into genexp
    >>> import ast, passmanager, backend
    >>> node = ast.parse("""                      \\n\
def foo(l):                                       \\n\
    return __builtin__.sum(l)                     \\n\
def bar(n):                                       \\n\
    return foo([x for x in __builtin__.range(n)]) \
""")
    >>> pm = passmanager.PassManager("test")
    >>> node = pm.apply(ListCompToGenexp, node)
    >>> print pm.dump(backend.Python, node)
    def foo(l):
        return __builtin__.sum(l)
    def bar(n):
        return foo((x for x in __builtin__.range(n)))
    '''
    def __init__(self):
        Transformation.__init__(self, NormalizeTuples,
                                PotentialIterator)

    def visit_ListComp(self, node):
        self.generic_visit(node)
        if node in self.potential_iterator:
            return ast.GeneratorExp(node.elt, node.generators)
        else:
            return node
