""" ConstantFolding performs some kind of partial evaluation.  """
from __future__ import print_function

from pythran.analyses import ConstantExpressions, Aliases, ASTMatcher
from pythran.passmanager import Transformation
from pythran.tables import MODULES, cxx_keywords
from pythran.conversion import to_ast, ConversionError, ToNotEval
from pythran.analyses.ast_matcher import DamnTooLongPattern
from pythran.syntax import PythranSyntaxError

import ast


class ConstantFolding(Transformation):

    """
    Replace constant expression by their evaluation.

    >>> import ast
    >>> from pythran import passmanager, backend
    >>> node = ast.parse("def foo(): return 1+3")
    >>> pm = passmanager.PassManager("test")
    >>> _, node = pm.apply(ConstantFolding, node)
    >>> print(pm.dump(backend.Python, node))
    def foo():
        return 4
    """

    def __init__(self):
        Transformation.__init__(self, ConstantExpressions, Aliases)

    def prepare(self, node, ctx):
        assert isinstance(node, ast.Module)
        self.env = {'__builtin__': __import__('__builtin__')}

        for module_name in MODULES:
            # __dispatch__ is the only fake top-level module
            if module_name != '__dispatch__':
                import_name = module_name

                # handle module name conflicting with c++ keywords
                if(module_name.endswith("_") and
                   module_name[:-1] in cxx_keywords):
                    import_name = module_name[:-1]
                self.env[module_name] = __import__(import_name)

                # handle functions conflicting with c++ keywords
                for fun in MODULES[module_name]:
                    if fun in ("__theitemgetter__", "pythran"):
                        # these ones do not exist in Python
                        continue
                    # Set attributs pointing to another for C++ keyword
                    # case of __builtin__.int_ that point on __builtin__.int
                    if not hasattr(self.env[module_name], fun):
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
                if(isinstance(node, ast.Index) and
                   not isinstance(new_node, ast.Index)):
                    new_node = ast.Index(new_node)
                try:
                    if not ASTMatcher(node).search(new_node):
                        self.update = True
                        return new_node
                except DamnTooLongPattern as e:
                    print("W: ", e, " Assume no update happened.")
                return Transformation.generic_visit(self, node)
            except ConversionError as e:
                print(ast.dump(node))
                print('error in constant folding: ', e)
                raise
            except ToNotEval:
                return Transformation.generic_visit(self, node)
            except AttributeError as e:
                # FIXME union_ function is not handle by constant folding
                if "union_" in e.args[0]:
                    return Transformation.generic_visit(self, node)
                elif "pythran" in e.args[0]:
                    # FIXME: Can be fix giving a Python implementation for
                    # these functions.
                    return Transformation.generic_visit(self, node)
                raise
            except NameError as e:
                # FIXME dispatched function are not processed by constant
                # folding
                if "__dispatch__" in e.args[0]:
                    return Transformation.generic_visit(self, node)
                raise
            except Exception as e:
                raise PythranSyntaxError(str(e), node)
        else:
            return Transformation.generic_visit(self, node)
