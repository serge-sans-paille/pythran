"""
ConstantFolding performs some kind of partial evaluation.
"""
import ast
from pythran.analyses import ConstantExpressions
from pythran.passmanager import Transformation
from pythran.tables import modules
from pythran.transformations import NormalizeTuples


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

    # maximum length of folded sequences
    # containers larger than this are not unfolded to limit code size growth
    MAX_LEN = 2 ** 8

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
                                 'True' if value else 'False', ast.Load())
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
