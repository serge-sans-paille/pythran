""" ListCompToMap transforms list comprehension into intrinsics.  """

from pythran.analyses import OptimizableComprehension
from pythran.passmanager import Transformation
from pythran.transformations import NormalizeTuples

import gast as ast
import sys

if sys.version_info.major == 2:
    MODULE = 'itertools'
    IFILTER = 'ifilter'
else:
    MODULE = '__builtin__'
    IFILTER = 'filter'


class ListCompToMap(Transformation):
    '''
    Transforms list comprehension into intrinsics.
    >>> import gast as ast
    >>> from pythran import passmanager, backend
    >>> node = ast.parse("[x*x for x in range(10)]")
    >>> pm = passmanager.PassManager("test")
    >>> _, node = pm.apply(ListCompToMap, node)
    >>> print pm.dump(backend.Python, node)
    __builtin__.map((lambda x: (x * x)), range(10))
    '''

    def __init__(self):
        Transformation.__init__(self, NormalizeTuples,
                                OptimizableComprehension)

    def visit_Module(self, node):
        self.use_itertools = False
        self.generic_visit(node)
        if self.use_itertools:
            importIt = ast.Import(
                names=[ast.alias(name='itertools', asname=None)])
            node.body.insert(0, importIt)
        return node

    def make_Iterator(self, gen):
        if gen.ifs:
            ldFilter = ast.Lambda(
                ast.arguments([ast.Name(gen.target.id, ast.Param(), None)],
                              None, [], [], None, []),
                ast.BoolOp(ast.And(), gen.ifs)
                if len(gen.ifs) > 1 else gen.ifs[0])
            self.use_itertools |= MODULE == 'itertools'
            ifilterName = ast.Attribute(
                value=ast.Name(id=MODULE,
                               ctx=ast.Load(),
                               annotation=None),
                attr=IFILTER, ctx=ast.Load())
            return ast.Call(ifilterName, [ldFilter, gen.iter], [])
        else:
            return gen.iter

    def visit_ListComp(self, node):

        if node in self.optimizable_comprehension:
            self.update = True
            self.generic_visit(node)

            iterList = []
            varList = []

            for gen in node.generators:
                iterList.append(self.make_Iterator(gen))
                varList.append(ast.Name(gen.target.id, ast.Param(), None))

            # If dim = 1, product is useless
            if len(iterList) == 1:
                iterAST = iterList[0]
                varAST = ast.arguments([varList[0]], None, [], [], None, [])
            else:
                self.use_itertools = True
                prodName = ast.Attribute(
                    value=ast.Name(id='itertools',
                                   ctx=ast.Load(),
                                   annotation=None),
                    attr='product', ctx=ast.Load())

                iterAST = ast.Call(prodName, iterList, [])
                varAST = ast.arguments([ast.Tuple(varList, ast.Store())],
                                       None, [], [], None, [])

            mapName = ast.Attribute(
                value=ast.Name(id='__builtin__',
                               ctx=ast.Load(),
                               annotation=None),
                attr='map', ctx=ast.Load())

            ldBodymap = node.elt
            ldmap = ast.Lambda(varAST, ldBodymap)

            return ast.Call(mapName, [ldmap, iterAST], [])

        else:
            return self.generic_visit(node)
