'''
This modules contains code transformation to turn pythran code into
optimized pythran code
    * ConstantUnfolding performs some kind of partial evaluation.
    * GenExpToImap tranforms generator expressions into iterators
'''

from analysis import ConstantExpressions, OptimizableGenexp
from passmanager import Transformation
from tables import modules
import ast


##
class ConstantFolding(Transformation):
    '''
    Replace constant expression by their evaluation.

    >>> import ast, passmanager, backend
    >>> node = ast.parse("def foo(): return 1+3")
    >>> pm = passmanager.PassManager("test")
    >>> node = pm.apply(ConstantFolding, node)
    >>> print pm.dump(backend.Python, node)
    def foo():
        return 4
    '''

    MAX_LEN = 2 ** 16

    class ConversionError(Exception):
        pass

    def __init__(self):
        Transformation.__init__(self, ConstantExpressions)

    def prepare(self, node, ctx):
        self.env = {'__builtin__': __import__('__builtin__')}
        class OperatorRenamer(ast.NodeTransformer):
            def visit_Import(self, node):
                for n in node.names:
                    if n.name == "operator_":
                        n.name = "operator"
                return node
        node = OperatorRenamer().visit(node)
        for module_name in modules:
            # module starting with "__" are pythran internal module and
            # should not be imported in the Python interpreter
            if not module_name.startswith('__'):
                if module_name == "operator_":
                    module_name = "operator"  # to import the python module
                    # operator instead of trying to import the module
                    # operator_ that does not exist
                self.env[module_name] = __import__(module_name)
        try:
            eval(compile(node, '<constant_folding>', 'exec'), self.env)
        except Exception as e:
            print ast.dump(node)
            print 'error in constant folding: ', e
            pass
        super(ConstantFolding, self).prepare(node, ctx)

    def to_ast(self, value):
        if any(isinstance(value, t)
                for t in (int, long, bool, float, complex)):
            return ast.Num(value)
        elif isinstance(value, str):
            return ast.Str(value)
        elif isinstance(value, list) and len(value) < ConstantFolding.MAX_LEN:
            #SG: unsure whether it Load or something else
            return ast.List(map(self.to_ast, value), ast.Load())
        elif isinstance(value, tuple) and len(value) < ConstantFolding.MAX_LEN:
            return ast.Tuple(map(self.to_ast, value), ast.Load())
        elif isinstance(value, set) and len(value) < ConstantFolding.MAX_LEN:
            return ast.Set(map(self.to_ast, value))
        elif isinstance(value, dict) and len(value) < ConstantFolding.MAX_LEN:
            keys = map(self.to_ast, value.iterkeys())
            values = map(self.to_ast, value.itervalues())
            return ast.Dict(keys, values)
        else:
            raise ConstantFolding.ConversionError()

    def generic_visit(self, node):
        if node in self.constant_expressions:
            try:
                fake_node = ast.Expression(
                        node.value if isinstance(node, ast.Index) else node)
                code = compile(fake_node, '<constant folding>', 'eval')
                value = eval(code, self.env)
                try:
                    new_node = self.to_ast(value)
                except ConstantFolding.ConversionError:
                    new_node = node
                if (isinstance(node, ast.Index)
                        and not isinstance(new_node, ast.Index)):
                    new_node = ast.Index(new_node)
                return new_node
            except Exception:  # as e:
                #print ast.dump(node)
                #print 'error in constant folding: ', e
                return node
        else:
            return Transformation.generic_visit(self, node)


class GenExpToImap(Transformation):
    '''
    Transforms generator expressions into iterators.

    >>> import ast, passmanager, backend
    >>> node = ast.parse("(x*x for x in range(10))")
    >>> pm = passmanager.PassManager("test")
    >>> node = pm.apply(GenExpToImap, node)
    >>> print pm.dump(backend.Python, node)
    import itertools
    itertools.imap((lambda x: (x * x)), range(10))
    '''

    def __init__(self):
        Transformation.__init__(self, OptimizableGenexp)

    def visit_Module(self, node):
        self.generic_visit(node)
        importIt = ast.Import(names=[ast.alias(name='itertools', asname=None)])
        node.body.insert(0, importIt)
        return node

    def make_Iterator(self, gen):
        if len(gen.ifs) == 0:
            return gen.iter
        else:
            ldFilter = ast.Lambda(
                ast.arguments([ast.Name(gen.target.id, ast.Store())],
                              None, None, []), ast.BoolOp(ast.And(), gen.ifs))
            ifilterName = ast.Attribute(
                value=ast.Name(id='itertools', ctx=ast.Load()),
                attr='ifilter', ctx=ast.Load())
            return ast.Call(ifilterName, [ldFilter, gen.iter], [], None, None)

    def visit_GeneratorExp(self, node):

        if node in self.optimizable_genexp:

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

            imapName = ast.Attribute(
                    value=ast.Name(id='itertools', ctx=ast.Load()),
                    attr='imap', ctx=ast.Load())

            ldBodyimap = node.elt
            ldimap = ast.Lambda(varAST, ldBodyimap)

            return ast.Call(imapName, [ldimap, iterAST], [], None, None)

        else:
            return self.generic_visit(node)
