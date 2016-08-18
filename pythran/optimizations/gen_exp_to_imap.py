""" GenExpToImap transforms generator expressions into iterators. """

from pythran.analyses import OptimizableComprehension
from pythran.passmanager import Transformation
from pythran.transformations import NormalizeTuples

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


class GenExpToImap(Transformation):
    '''
    Transforms generator expressions into iterators.

    >>> import gast as ast
    >>> from pythran import passmanager, backend
    >>> node = ast.parse("(x*x for x in range(10))")
    >>> pm = passmanager.PassManager("test")
    >>> _, node = pm.apply(GenExpToImap, node)
    >>> print pm.dump(backend.Python, node)
    import itertools
    itertools.imap((lambda x: (x * x)), range(10))
    '''

    def __init__(self):
        Transformation.__init__(self, NormalizeTuples,
                                OptimizableComprehension)

    def visit_Module(self, node):
        self.generic_visit(node)
        if MODULE != '__builtin__':
            importIt = ast.Import(names=[ast.alias(name=MODULE, asname=None)])
            node.body.insert(0, importIt)
        return node

    def make_Iterator(self, gen):
        if gen.ifs:
            ldFilter = ast.Lambda(
                ast.arguments([ast.Name(gen.target.id, ast.Param(), None)],
                              None, [], [], None, []),
                ast.BoolOp(ast.And(), gen.ifs)
                if len(gen.ifs) > 1 else gen.ifs[0])
            ifilterName = ast.Attribute(
                value=ast.Name(id=MODULE,
                               ctx=ast.Load(),
                               annotation=None),
                attr=IFILTER, ctx=ast.Load())
            return ast.Call(ifilterName, [ldFilter, gen.iter], [])
        else:
            return gen.iter

    def visit_GeneratorExp(self, node):

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
                prodName = ast.Attribute(
                    value=ast.Name(id='itertools',
                                   ctx=ast.Load(),
                                   annotation=None),
                    attr='product', ctx=ast.Load())

                iterAST = ast.Call(prodName, iters, [])
                varAST = ast.arguments([ast.Tuple(variables, ast.Store())],
                                       None, [], [], None, [])

            imapName = ast.Attribute(
                value=ast.Name(id=MODULE,
                               ctx=ast.Load(),
                               annotation=None),
                attr=IMAP, ctx=ast.Load())

            ldBodyimap = node.elt
            ldimap = ast.Lambda(varAST, ldBodyimap)

            return ast.Call(imapName, [ldimap, iterAST], [])

        else:
            return self.generic_visit(node)
