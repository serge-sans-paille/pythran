'''
This modules contains code transformation to turn pythran code into
optimized pythran code
    * ConstantUnfolding performs some kind of partial evaluation.
    * GenExpToImap transforms generator expressions into iterators
    * ListCompToMap transforms list comprehension into intrinsics.
    * ListCompToGenexp transforms list comprehension into genexp
    * IterTransformation replaces expressions by iterators when possible.
    * LoopFullUnrolling fully unrolls loops with static bounds
'''

from analysis import ConstantExpressions, OptimizableComprehension
from analysis import PotentialIterator, Aliases, UseOMP, HasBreak, HasContinue
from passmanager import Transformation
from tables import modules, equivalent_iterators
from passes import NormalizeTuples, RemoveNestedFunctions, RemoveLambdas
import ast
from copy import deepcopy


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

        for module_name in modules:
            not_builtin = ["__builtin__", "__exception__", "__dispatch__",
                "__iterator__"]
            # module starting with "__" are pythran internal module and
            # should not be imported in the Python interpreter
            if not module_name.startswith('__'):
                import_name = module_name
                if module_name == "operator_":
                    import_name = "operator"
                self.env[module_name] = __import__(import_name)
            elif module_name not in not_builtin:
                try:
                    self.env[module_name] = __import__(module_name.strip('_'))
                except:
                    try:
                        # should try from another package than builtin,
                        # e.g. for ndarray
                        self.env[module_name] = getattr(
                                self.env['__builtin__'],
                                module_name.strip('_'))
                    except:
                        pass

        try:
            eval(compile(node, '<constant_folding>', 'exec'), self.env)
        except Exception as e:
            print ast.dump(node)
            print 'error in constant folding: ', e
            pass
        super(ConstantFolding, self).prepare(node, ctx)

    def to_ast(self, value):
        if (type(value) in (int, long, float, complex)):
            return ast.Num(value)
        elif isinstance(value, bool):
            return ast.Attribute(ast.Name('__builtin__', ast.Load()),
                    'True' if value else False)
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
                new_node = self.to_ast(value)
                if (isinstance(node, ast.Index)
                        and not isinstance(new_node, ast.Index)):
                    new_node = ast.Index(new_node)
                return new_node
            except Exception:  # as e:
                #print ast.dump(node)
                #print 'error in constant folding: ', e
                return Transformation.generic_visit(self, node)
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
        Transformation.__init__(self, NormalizeTuples,
                                OptimizableComprehension)

    def visit_Module(self, node):
        self.generic_visit(node)
        importIt = ast.Import(names=[ast.alias(name='itertools', asname=None)])
        node.body.insert(0, importIt)
        return node

    def make_Iterator(self, gen):
        if gen.ifs:
            ldFilter = ast.Lambda(
                ast.arguments([ast.Name(gen.target.id, ast.Store())],
                              None, None, []), ast.BoolOp(ast.And(), gen.ifs))
            ifilterName = ast.Attribute(
                value=ast.Name(id='itertools', ctx=ast.Load()),
                attr='ifilter', ctx=ast.Load())
            return ast.Call(ifilterName, [ldFilter, gen.iter], [], None, None)
        else:
            return gen.iter

    def visit_GeneratorExp(self, node):

        if node in self.optimizable_comprehension:

            self.generic_visit(node)

            iters = [self.make_Iterator(gen) for gen in node.generators]
            variables = [ast.Name(gen.target.id, ast.Param())
                         for gen in node.generators]

            # If dim = 1, product is useless
            if len(iters) == 1:
                iterAST = iters[0]
                varAST = ast.arguments([variables[0]], None, None, [])
            else:
                prodName = ast.Attribute(
                    value=ast.Name(id='itertools', ctx=ast.Load()),
                    attr='product', ctx=ast.Load())

                iterAST = ast.Call(prodName, iters, [], None, None)
                varAST = ast.arguments([ast.Tuple(variables, ast.Store())],
                                   None, None, [])

            imapName = ast.Attribute(
                    value=ast.Name(id='itertools', ctx=ast.Load()),
                    attr='imap', ctx=ast.Load())

            ldBodyimap = node.elt
            ldimap = ast.Lambda(varAST, ldBodyimap)

            return ast.Call(imapName, [ldimap, iterAST], [], None, None)

        else:
            return self.generic_visit(node)


##
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


##
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


##
class IterTransformation(Transformation):
    '''
    Replaces expressions by iterators when possible.

    >>> import ast, passmanager, backend
    >>> node = ast.parse("""                      \\n\
def foo(l):                                       \\n\
    return __builtin__.sum(l)                     \\n\
def bar(n):                                       \\n\
    return foo(__builtin__.range(n)) \
""")
    >>> pm = passmanager.PassManager("test")
    >>> node = pm.apply(IterTransformation, node)
    >>> print pm.dump(backend.Python, node)
    import itertools
    def foo(l):
        return __builtin__.sum(l)
    def bar(n):
        return foo(__builtin__.xrange(n))
    '''
    def __init__(self):
        Transformation.__init__(self, PotentialIterator, Aliases)

    def find_matching_builtin(self, node):
        if node.func in self.aliases:
            for k, v in self.aliases.iteritems():
                if (isinstance(k, ast.Attribute)
                    and isinstance(k.value, ast.Name)):
                    if k.value.id == "__builtin__":
                        if self.aliases[node.func].aliases == v.aliases:
                            return k.attr

    def visit_Module(self, node):
        self.generic_visit(node)
        importIt = ast.Import(names=[ast.alias(name='itertools', asname=None)])
        return ast.Module(body=([importIt] + node.body))

    def visit_Call(self, node):
        if node in self.potential_iterator:
            f = self.find_matching_builtin(node)
            if f in equivalent_iterators:
                (ns, new) = equivalent_iterators[f]
                node.func = ast.Attribute(
                    value=ast.Name(id=ns, ctx=ast.Load()),
                    attr=new, ctx=ast.Load())
        return self.generic_visit(node)


##
class Pow2(Transformation):
    '''
    Replaces **2 by a call to pow2

    >>> import ast, passmanager, backend
    >>> node = ast.parse('a**2')
    >>> pm = passmanager.PassManager("test")
    >>> node = pm.apply(Pow2, node)
    >>> print pm.dump(backend.Python, node)
    __builtin__.pow2(a)
    '''

    def visit_BinOp(self, node):
        self.generic_visit(node)
        if (type(node.op) is ast.Pow
                and type(node.right) is ast.Num
                and node.right.n == 2):
            return ast.Call(
                    ast.Attribute(
                        ast.Name('__builtin__', ast.Load()),
                        'pow2',
                        ast.Load()),
                    [node.left],
                    [],
                    None,
                    None
                    )
        else:
            return node


##
class LoopFullUnrolling(Transformation):
    '''
    Fully unroll loops with static bounds

    >>> import ast, passmanager, backend
    >>> node = ast.parse('for j in [1,2,3]: i += j')
    >>> pm = passmanager.PassManager("test")
    >>> node = pm.apply(LoopFullUnrolling, node)
    >>> print pm.dump(backend.Python, node)
    if 1:
        j = 1
        i += j
    if 1:
        j = 2
        i += j
    if 1:
        j = 3
        i += j
    '''

    MAX_ITER = 64

    def visit_For(self, node):
        self.generic_visit(node)
        use_omp = self.passmanager.gather(UseOMP, node, self.ctx)
        has_break = any(self.passmanager.gather(HasBreak, n, self.ctx)
                for n in node.body)
        has_cont = any(self.passmanager.gather(HasContinue, n, self.ctx)
                for n in node.body)
        if type(node.iter) is ast.List:
            if (not use_omp and
                    not has_break and
                    not has_cont and
                    len(node.iter.elts) < LoopFullUnrolling.MAX_ITER):
                elts = node.iter.elts
                block = []
                for elt in elts:
                    block.append(
                            ast.If(ast.Num(1),
                                [ast.Assign([deepcopy(node.target)], elt)]
                                + deepcopy(node.body),
                                []
                                )
                            )
                return block
        return node
