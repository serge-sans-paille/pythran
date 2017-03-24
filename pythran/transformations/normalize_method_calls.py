""" NormalizeMethodCalls turns built in method calls into function calls. """

from pythran.analyses import Globals
from pythran.passmanager import Transformation
from pythran.syntax import PythranSyntaxError
from pythran.tables import attributes, functions, methods, MODULES
from pythran.conversion import mangle, demangle

import gast as ast
from functools import reduce


class NormalizeMethodCalls(Transformation):
    '''
    Turns built in method calls into function calls.

    >>> import gast as ast
    >>> from pythran import passmanager, backend
    >>> node = ast.parse("l.append(12)")
    >>> pm = passmanager.PassManager("test")
    >>> _, node = pm.apply(NormalizeMethodCalls, node)
    >>> print pm.dump(backend.Python, node)
    __builtin__.list.append(l, 12)
    '''

    def __init__(self):
        Transformation.__init__(self, Globals)
        self.imports = {'__builtin__': '__builtin__'}
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
        self.skip_functions = True
        self.generic_visit(node)
        self.skip_functions = False
        self.generic_visit(node)
        new_imports = self.to_import - self.globals
        imports = [ast.Import(names=[ast.alias(name=mod[17:], asname=mod)])
                   for mod in new_imports]
        node.body = imports + node.body
        self.update |= bool(imports)
        return node

    def visit_FunctionDef(self, node):
        if self.skip_functions:
            return node
        old_imports = self.imports
        self.imports = old_imports.copy()
        for arg in node.args.args:
            self.imports.pop(arg.id, None)
        self.generic_visit(node)

        self.imports = old_imports

        return node

    def visit_Import(self, node):
        for alias in node.names:
            name = alias.asname or alias.name
            self.imports[name] = name
        return node

    def visit_Assign(self, node):
        # aliasing between modules
        if isinstance(node.value, ast.Name) and node.value.id in self.imports:
            for t in node.targets:
                if isinstance(t, ast.Name):
                    self.imports[t.id] = self.imports[node.value.id]
            return None
        else:
            n = self.generic_visit(node)
            for t in node.targets:
                if isinstance(t, ast.Name):
                    self.imports.pop(t.id, None)
            return n

    def visit_For(self, node):
        node.iter = self.visit(node.iter)
        if isinstance(node.target, ast.Name):
            self.imports.pop(node.target.id, None)
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
            module_id = self.imports[node.value.id]
            if node.attr not in MODULES[self.renamer(module_id, MODULES)[1]]:
                msg = ("`" + node.attr + "' is not a member of " +
                       module_id + " or Pythran does not support it")
                raise PythranSyntaxError(msg, node)
            node.value.id = module_id  # patch module aliasing
            self.update = True
            return node
        # not listed as attributed -> not a getattr
        elif node.attr not in attributes:
            return node
        # A getattr !
        else:
            self.update = True
            return ast.Call(
                ast.Attribute(
                    ast.Name('__builtin__', ast.Load(), None),
                    'getattr',
                    ast.Load()),
                [node.value, ast.Str(node.attr)],
                [])

    @staticmethod
    def renamer(v, cur_module):
        """
        Rename function path to fit Pythonic naming.
        """
        mname = demangle(v)

        name = v + '_'
        if name in cur_module:
            return name, mname
        else:
            return v, mname

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
                    self.to_import.add(mangle(mod[0]))
                    node.func = reduce(
                        lambda v, o: ast.Attribute(v, o, ast.Load()),
                        mod[1:] + (node.func.attr,),
                        ast.Name(mangle(mod[0]), ast.Load(), None)
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
                        new_id, mname = self.renamer(path.attr, cur_module)
                        return (ast.Attribute(new_node, new_id, ast.Load()),
                                cur_module[mname])
                    else:
                        new_id, mname = self.renamer(path.id, cur_module)
                        return (ast.Name(new_id, ast.Load(), None),
                                cur_module[mname])

                # Rename module path to avoid naming issue.
                node.func.value, _ = rec(node.func.value, MODULES)
                self.update = True

        return node

    def visit_BinOp(self, node):
        # replace "str" % (...) by __builtin__.str.__mod__(...)
        # the reason why we do this is that % formatting is handled by
        # a third party library that's relatively costly to load, so using a
        # function name instead of an operator overload makes it possible to
        # load it only when needed. The drawback is that % formatting is no
        # longer supported when lhs is not a literal
        self.generic_visit(node)
        if isinstance(node.op, ast.Mod) and isinstance(node.left, ast.Str):
            self.update = True
            return ast.Call(
                ast.Attribute(
                    ast.Attribute(
                        ast.Name('__builtin__', ast.Load(), None),
                        'str',
                        ast.Load()),
                    '__mod__',
                    ast.Load()),
                [node.left, node.right],
                [])
        return node
