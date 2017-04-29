
""" Comprehension patterns transforms list comprehension into intrinsics.  """

from pythran.analyses import OptimizableComprehension
from pythran.passmanager import Transformation
from pythran.transformations.normalize_tuples import ConvertToTuple
from pythran.conversion import mangle

import gast as ast
import sys

if sys.version_info.major == 2:
    MODULE = 'itertools'
    IMAP = 'imap'
    IFILTER = 'ifilter'
else:
    MODULE = '__builtin__'
    IMAP = 'map'
    IFILTER = 'filter'
ASMODULE = mangle(MODULE)


class ComprehensionPatterns(Transformation):
    '''
    Transforms list comprehension into intrinsics.
    >>> import gast as ast
    >>> from pythran import passmanager, backend
    >>> node = ast.parse("[x*x for x in range(10)]")
    >>> pm = passmanager.PassManager("test")
    >>> _, node = pm.apply(ComprehensionPatterns, node)
    >>> print pm.dump(backend.Python, node)
    __builtin__.map((lambda x: (x * x)), range(10))

    >>> node = ast.parse("(x*x for x in range(10))")
    >>> pm = passmanager.PassManager("test")
    >>> _, node = pm.apply(ComprehensionPatterns, node)
    >>> print pm.dump(backend.Python, node)
    import itertools as __pythran_import_itertools
    __pythran_import_itertools.imap((lambda x: (x * x)), range(10))
    '''

    def __init__(self):
        Transformation.__init__(self, OptimizableComprehension)

    def visit_Module(self, node):
        self.use_itertools = False
        self.generic_visit(node)
        if self.use_itertools:
            import_alias = ast.alias(name='itertools',
                                     asname=mangle('itertools'))
            importIt = ast.Import(names=[import_alias])
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
                value=ast.Name(id=ASMODULE,
                               ctx=ast.Load(),
                               annotation=None),
                attr=IFILTER, ctx=ast.Load())
            return ast.Call(ifilterName, [ldFilter, gen.iter], [])
        else:
            return gen.iter

    def visitComp(self, node, make_attr):

        if node in self.optimizable_comprehension:
            self.update = True
            self.generic_visit(node)

            iters = [self.make_Iterator(gen) for gen in node.generators]
            variables = [ast.Name(gen.target.id, ast.Param(), None)
                         for gen in node.generators]

            # If dim = 1, product is useless
            if len(iters) == 1:
                iterAST = iters[0]
                varAST = ast.arguments([variables[0]], None, [], [], None, [])
            else:
                self.use_itertools = True
                prodName = ast.Attribute(
                    value=ast.Name(id=mangle('itertools'),
                                   ctx=ast.Load(),
                                   annotation=None),
                    attr='product', ctx=ast.Load())

                varid = variables[0].id  # retarget this id, it's free
                renamings = {v.id: (i,) for i, v in enumerate(variables)}
                node.elt = ConvertToTuple(varid, renamings).visit(node.elt)
                iterAST = ast.Call(prodName, iters, [])
                varAST = ast.arguments([ast.Name(varid, ast.Param(), None)],
                                       None, [], [], None, [])

            mapName = make_attr()
            ldBodymap = node.elt
            ldmap = ast.Lambda(varAST, ldBodymap)

            return ast.Call(mapName, [ldmap, iterAST], [])

        else:
            return self.generic_visit(node)

    def visit_ListComp(self, node):
        def makeattr():
            return ast.Attribute(
                value=ast.Name(id='__builtin__',
                               ctx=ast.Load(),
                               annotation=None),
                attr='map', ctx=ast.Load())
        return self.visitComp(node, makeattr)

    def visit_GeneratorExp(self, node):
        def makeattr():
            self.use_itertools |= MODULE == 'itertools'
            return ast.Attribute(
                value=ast.Name(id=ASMODULE,
                               ctx=ast.Load(),
                               annotation=None),
                attr=IMAP, ctx=ast.Load())
        return self.visitComp(node, makeattr)
