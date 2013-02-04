'''
This modules contains code transformation to turn pythran code into
optimized pythran code
    * ConstantUnfolding performs some kind of partial evaluation.
'''

from analysis import ConstantExpressions
from passmanager import Transformation
from tables import modules
import ast


##
class ConstantFolding(Transformation):
    '''
    Replace constant expression by their evaluation.
    >>> import ast, passmanager, backend
    >>> node = ast.parse("def foo(): return len(range(5))")
    >>> pm = passmanager.PassManager("test")
    >>> pm.apply(ConstantFolding, node)
    >>> print pm.dump(backend.Python, node)
    <BLANKLINE>
    <BLANKLINE>
    def foo():
        return 5
    '''

    MAX_LEN = 2 ** 16

    INIT_CODE = '''
__list__ = list
__dict__ = dict
__set__ = set
'''

    class ConversionError(Exception):
        pass

    def __init__(self):
        Transformation.__init__(self, ConstantExpressions)

    def run_visit(self, node):
        self.env = dict()
        try:
            eval(
                    compile(
                        ast.parse(ConstantFolding.INIT_CODE),
                        '<constant_folding>',
                        'exec'),
                    self.env)
            eval(compile(node, '<constant_folding>', 'exec'), self.env)
        except Exception as e:
            print ast.dump(node)
            print 'error in constant folding: ', e
            pass
        for module_name in modules:
            if not module_name.startswith('__'):
                self.env[module_name] = __import__(module_name)
        self.visit(node)

    def to_ast(self, value):
        if any(isinstance(value, t)
                for t in (int, long, bool, float, complex)):
            return ast.Num(value)
        elif isinstance(value, str):
            return ast.Str(value)
        elif isinstance(value, list) and len(value) < ConstantFolding.MAX_LEN:
            #SG: unsure whether it Load or something else
            return ast.List([self.to_ast(elt) for elt in value], ast.Load())
        elif isinstance(value, tuple) and len(value) < ConstantFolding.MAX_LEN:
            return ast.Tuple([self.to_ast(elt) for elt in value], ast.Load())
        elif isinstance(value, set) and len(value) < ConstantFolding.MAX_LEN:
            return ast.Set([self.to_ast(elt) for elt in value])
        elif isinstance(value, dict) and len(value) < ConstantFolding.MAX_LEN:
            return ast.Dict(
                    [self.to_ast(elt) for elt in value.iterkeys()],
                    [self.to_ast(elt) for elt in value.itervalues()]
                    )
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
            except Exception as e:
                #print ast.dump(node)
                #print 'error in constant folding: ', e
                return node
        else:
            return Transformation.generic_visit(self, node)
