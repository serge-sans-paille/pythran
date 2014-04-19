"""
ListCompToMap transforms list comprehension into intrinsics.
"""
import ast
from pythran.analyses import OptimizableComprehension
from pythran.passmanager import Transformation
from pythran.transformations import NormalizeTuples


class ListCompToMap(Transformation):
    '''
    Transforms list comprehension into intrinsics.
    >>> import ast, passmanager, backend
    >>> node = ast.parse("[x*x for x in range(10)]")
    >>> pm = passmanager.PassManager("test")
    >>> node = pm.apply(ListCompToMap, node)
    >>> print pm.dump(backend.Python, node)
    __builtin__.map((lambda x: (x * x)), range(10))
    '''

    def __init__(self):
        Transformation.__init__(self, NormalizeTuples,
                                OptimizableComprehension)

    def make_Iterator(self, gen):
        if gen.ifs:
            ldFilter = ast.Lambda(
                ast.arguments([ast.Name(gen.target.id, ast.Param())],
                              None, None, []), ast.BoolOp(ast.And(), gen.ifs))
            ifilterName = ast.Attribute(
                value=ast.Name(id='itertools', ctx=ast.Load()),
                attr='ifilter', ctx=ast.Load())
            return ast.Call(ifilterName, [ldFilter, gen.iter], [], None, None)
        else:
            return gen.iter

    def visit_ListComp(self, node):

        if node in self.optimizable_comprehension:

            self.generic_visit(node)

            iterList = []
            varList = []

            for gen in node.generators:
                iterList.append(self.make_Iterator(gen))
                varList.append(ast.Name(gen.target.id, ast.Param()))

            # If dim = 1, product is useless
            if len(iterList) == 1:
                iterAST = iterList[0]
                varAST = ast.arguments([varList[0]], None, None, [])
            else:
                prodName = ast.Attribute(
                    value=ast.Name(id='itertools', ctx=ast.Load()),
                    attr='product', ctx=ast.Load())

                iterAST = ast.Call(prodName, iterList, [], None, None)
                varAST = ast.arguments([ast.Tuple(varList, ast.Store())],
                                       None, None, [])

            mapName = ast.Attribute(
                value=ast.Name(id='__builtin__', ctx=ast.Load()),
                attr='map', ctx=ast.Load())

            ldBodymap = node.elt
            ldmap = ast.Lambda(varAST, ldBodymap)

            return ast.Call(mapName, [ldmap, iterAST], [], None, None)

        else:
            return self.generic_visit(node)
