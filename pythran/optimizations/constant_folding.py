"""
ConstantFolding performs some kind of partial evaluation.
"""

from pythran.analyses import ConstantExpressions, Aliases
from pythran.passmanager import Transformation
from pythran.tables import modules, cxx_keywords
from pythran.conversion import to_ast, ConversionError, ToNotEval

import types
import ast
import itertools
import numpy


class ConstantFolding(Transformation):
    '''
    Replace constant expression by their evaluation.

    >>> import ast
    >>> from pythran import passmanager, backend
    >>> node = ast.parse("def foo(): return 1+3")
    >>> pm = passmanager.PassManager("test")
    >>> node = pm.apply(ConstantFolding, node)
    >>> print pm.dump(backend.Python, node)
    def foo():
        return 4
    '''

    def __init__(self):
        Transformation.__init__(self, ConstantExpressions, Aliases)

    def prepare(self, node, ctx):
        assert(isinstance(node, ast.Module))
        self.env = {'__builtin__': __import__('__builtin__')}

        for module_name in modules:
            not_builtin = ["__builtin__", "__exception__", "__dispatch__",
                           "__iterator__"]
            # module starting with "__" are pythran internal module and
            # should not be imported in the Python interpreter
            if not module_name.startswith('__'):
                import_name = module_name
                if (module_name.endswith("_")
                        and module_name[:-1] in cxx_keywords):
                    import_name = module_name[:-1]
                self.env[module_name] = __import__(import_name)
            elif module_name not in not_builtin:
                if module_name in ("__ndarray__", "__finfo__"):
                    self.env[module_name] = \
                        eval("numpy." + module_name.strip("_"))
                else:
                    self.env[module_name] = getattr(
                        self.env['__builtin__'],
                        module_name.strip('_'))

            # hack to handle int_, bool_, ... builtins functions
            builtin_types = ("__list__", "__set__", "__dict__", "__str__",
                             "__file__", "__exception__", "__dispatch__",
                             "__iterator__")
            if module_name not in builtin_types:
                for fun in modules[module_name]:
                    if fun == "__theitemgetter__":
                        # I have no idea about how return_call work and what is
                        # the trick here...
                        continue
                    # Set attributs pointing to another for C++ keyword
                    # case of __builtin__.int_ that point on __builtin__.int
                    elif (not hasattr(self.env[module_name], fun)
                          and fun.endswith("_")):
                        setattr(self.env[module_name], fun,
                                getattr(self.env[module_name], fun.strip("_")))

        # we need to parse the whole code to be able to apply user-defined pure
        # function but import are resolved before so we remove them to avoid
        # ImportError (for operator_ for example)
        dummy_module = ast.Module([s for s in node.body
                                   if not isinstance(s, ast.Import)])
        eval(compile(dummy_module, '<constant_folding>', 'exec'), self.env)

        super(ConstantFolding, self).prepare(node, ctx)

    def generic_visit(self, node):
        if node in self.constant_expressions:
            try:
                fake_node = ast.Expression(
                    node.value if isinstance(node, ast.Index) else node)
                code = compile(fake_node, '<constant folding>', 'eval')
                value = eval(code, self.env)
                new_node = to_ast(value)
                if (isinstance(node, ast.Index)
                        and not isinstance(new_node, ast.Index)):
                    new_node = ast.Index(new_node)
                return new_node
            except ConversionError as e:
                print ast.dump(node)
                print 'error in constant folding: ', e
                raise
            except ToNotEval:
                return Transformation.generic_visit(self, node)
            except AttributeError as e:
                # FIXME union_ function is not handle by constant folding
                if "union_" in e.args[0]:
                    return Transformation.generic_visit(self, node)
                raise
            except NameError as e:
                # FIXME dispatched function are not processed by constant
                # folding
                if "__dispatch__" in e.args[0]:
                    return Transformation.generic_visit(self, node)
                raise
        else:
            return Transformation.generic_visit(self, node)
