""" NormalizeMethodCalls turns built in method calls into function calls. """

from pythran.analyses import Globals
from pythran.passmanager import Transformation
from pythran.syntax import PythranSyntaxError
from pythran.tables import attributes, functions, methods, MODULES

import ast


class NormalizeMethodCalls(Transformation):
    '''
    Turns built in method calls into function calls.

    >>> import ast
    >>> from pythran import passmanager, backend
    >>> node = ast.parse("l.append(12)")
    >>> pm = passmanager.PassManager("test")
    >>> _, node = pm.apply(NormalizeMethodCalls, node)
    >>> print pm.dump(backend.Python, node)
    __builtin__.list.append(l, 12)
    '''

    def __init__(self):
        Transformation.__init__(self, Globals)
        self.imports = set()
        self.to_import = set()

    def visit_Module(self, node):
        """
            When we normalize call, we need to add correct import for method
            to function transformation.

            a.max()

            for numpy array will become:

            numpy.max(a)

            so we have to import numpy.
        """
        self.generic_visit(node)
        new_imports = self.to_import - self.globals
        imports = [ast.Import(names=[ast.alias(name=mod, asname=None)])
                   for mod in new_imports]
        node.body = imports + node.body
        self.update |= bool(imports)
        return node

    def visit_FunctionDef(self, node):
        self.imports = self.globals.copy()
        [self.imports.discard(arg.id) for arg in node.args.args]
        self.generic_visit(node)
        return node

    def visit_Import(self, node):
        for alias in node.names:
            self.imports.add(alias.asname or alias.name)
        return node

    def visit_Assign(self, node):
        n = self.generic_visit(node)
        for t in node.targets:
            if isinstance(t, ast.Name):
                self.imports.discard(t.id)
        return n

    def visit_For(self, node):
        node.iter = self.visit(node.iter)
        if isinstance(node.target, ast.Name):
            self.imports.discard(node.target.id)
        if node.body:
            node.body = [self.visit(n) for n in node.body]
        if node.orelse:
            node.orelse = [self.visit(n) for n in node.orelse]
        return node

    def visit_Attribute(self, node):
        node = self.generic_visit(node)
        # storing in an attribute -> not a getattr
        if not isinstance(node.ctx, ast.Load):
            return node
        # method name -> not a getattr
        elif node.attr in methods:
            return node
        # imported module -> not a getattr
        elif (isinstance(node.value, ast.Name) and
              node.value.id in self.imports):
            if node.attr not in MODULES[node.value.id]:
                msg = ("`" + node.attr + "' is not a member of " +
                       node.value.id + " or Pythran does not support it")
                raise PythranSyntaxError(msg, node)
            return node
        # not listed as attributed -> not a getattr
        elif node.attr not in attributes:
            return node
        # A getattr !
        else:
            self.update = True
            return ast.Call(ast.Attribute(ast.Name('__builtin__', ast.Load()),
                                          'getattr',
                                          ast.Load()),
                            [node.value, ast.Str(node.attr)],
                            [], None, None)

    @staticmethod
    def renamer(v, cur_module):
        """
        Rename function path to fit Pythonic naming.
        """
        name = v + '_'
        if name in cur_module:
            return name
        else:
            return v

    def visit_Call(self, node):
        """
        Transform call site to have normal function call.

        Examples
        --------
        For methods:
        >> a = [1, 2, 3]

        >> a.append(1)

        Becomes

        >> __list__.append(a, 1)


        For functions:
        >> __builtin__.dict.fromkeys([1, 2, 3])

        Becomes

        >> __builtin__.__dict__.fromkeys([1, 2, 3])
        """
        node = self.generic_visit(node)
        # Only attributes function can be Pythonic and should be normalized
        if isinstance(node.func, ast.Attribute):
            if node.func.attr in methods:
                # Get object targeted by methods
                obj = lhs = node.func.value
                # Get the most left identifier to check if it is not an
                # imported module
                while isinstance(obj, ast.Attribute):
                    obj = obj.value
                is_not_module = (not isinstance(obj, ast.Name) or
                                 obj.id not in self.imports)

                if is_not_module:
                    self.update = True
                    # As it was a methods call, push targeted object as first
                    # arguments and add correct module prefix
                    node.args.insert(0, lhs)
                    mod = methods[node.func.attr][0]
                    # Submodules import full module
                    self.to_import.add(mod[0])
                    node.func = reduce(
                        lambda v, o: ast.Attribute(v, o, ast.Load()),
                        mod[1:] + (node.func.attr,),
                        ast.Name(mod[0], ast.Load())
                        )
                # else methods have been called using function syntax
            if node.func.attr in methods or node.func.attr in functions:
                # Now, methods and function have both function syntax
                def rec(path, cur_module):
                    """
                    Recursively rename path content looking in matching module.

                    Prefers __module__ to module if it exists.
                    This recursion is done as modules are visited top->bottom
                    while attributes have to be visited bottom->top.
                    """
                    err = "Function path is chained attributes and name"
                    assert isinstance(path, (ast.Name, ast.Attribute)), err
                    if isinstance(path, ast.Attribute):
                        new_node, cur_module = rec(path.value, cur_module)
                        new_id = self.renamer(path.attr, cur_module)
                        return (ast.Attribute(new_node, new_id, ast.Load()),
                                cur_module[new_id])
                    else:
                        new_id = self.renamer(path.id, cur_module)
                        return ast.Name(new_id, ast.Load()), cur_module[new_id]

                # Rename module path to avoid naming issue.
                node.func.value, _ = rec(node.func.value, MODULES)
                self.update = True

        return node
