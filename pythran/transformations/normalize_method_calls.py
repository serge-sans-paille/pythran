"""
NormalizeMethodCalls turns built in method calls into function calls
"""
import ast
from pythran.analyses import Globals
from pythran.passmanager import Transformation
from pythran.tables import attributes, functions, methods, modules, namespace


class NormalizeMethodCalls(Transformation):
    '''
    Turns built in method calls into function calls.

    >>> import ast, passmanager, backend
    >>> node = ast.parse("l.append(12)")
    >>> pm = passmanager.PassManager("test")
    >>> node = pm.apply(NormalizeMethodCalls, node)
    >>> print pm.dump(backend.Python, node)
    __list__.append(l, 12)
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
        imports = [ast.Import(names=[ast.alias(name=mod,
                                     asname=namespace + "::" + mod)])
                   for mod in new_imports]
        node.body = imports + node.body
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
        if type(node.ctx) is not ast.Load:
            return node
        # method name -> not a getattr
        elif node.attr in methods:
            return node
        # imported module -> not a getattr
        elif type(node.value) is ast.Name and node.value.id in self.imports:
            return node
        # not listed as attributed -> not a getattr
        elif node.attr not in attributes:
            return node
        # A getattr !
        else:
            return ast.Call(ast.Attribute(ast.Name('__builtin__', ast.Load()),
                                          'getattr',
                                          ast.Load()),
                            [node.value, ast.Str(node.attr)],
                            [], None, None)

    def visit_Call(self, node):
        node = self.generic_visit(node)
        if isinstance(node.func, ast.Attribute):
            lhs = node.func.value
            if node.func.attr in methods:
                isname = isinstance(lhs, ast.Name)
                ispath = isname or isinstance(lhs, ast.Attribute)
                if not ispath or (isname and lhs.id not in self.imports):
                    node.args.insert(0, node.func.value)
                    mod = methods[node.func.attr][0]
                    self.to_import.add(mod)
                    node.func = ast.Attribute(
                        ast.Name(mod, ast.Load()),
                        node.func.attr,
                        ast.Load())
            if node.func.attr in methods or node.func.attr in functions:
                def renamer(v):
                    name = '__{0}__'.format(v)
                    if name in modules:
                        return name
                    else:
                        name += '_'
                        if name in modules:
                            return name
                    return v

                def rec(n):
                    if isinstance(n, ast.Attribute):
                        n.attr = renamer(n.attr)
                        rec(n.value)
                    elif isinstance(n, ast.Name):
                        n.id = renamer(n.id)
                rec(node.func.value)

        return node
