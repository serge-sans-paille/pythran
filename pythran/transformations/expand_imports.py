"""
ExpandImports replaces imports by their full paths
"""
import ast
from pythran.passmanager import Transformation
from pythran.tables import namespace


class ExpandImports(Transformation):
    '''
    Expands all imports into full paths.

    >>> import ast, passmanager, backend
    >>> node = ast.parse("from math import cos ; cos(2)")
    >>> pm = passmanager.PassManager("test")
    >>> node = pm.apply(ExpandImports, node)
    >>> print pm.dump(backend.Python, node)
    import math as pythonic::math
    math.cos(2)
    '''

    def __init__(self):
        Transformation.__init__(self)
        self.imports = set()
        self.symbols = dict()

    def visit_Module(self, node):
        node.body = [k for k in (self.visit(n) for n in node.body) if k]
        imports = [ast.Import([ast.alias(i, namespace + "::" + i)])
                   for i in self.imports]
        node.body = imports + node.body
        ast.fix_missing_locations(node)
        return node

    def visit_Import(self, node):
        for alias in node.names:
            self.imports.add(alias.name)
            self.symbols[alias.asname or alias.name] = (alias.name,)
        return None

    def visit_ImportFrom(self, node):
        self.imports.add(node.module)
        for alias in node.names:
            self.symbols[alias.asname or alias.name] = (
                node.module,
                alias.name,
                )
        return None

    def visit_FunctionDef(self, node):
        self.symbols.pop(node.name, None)
        gsymbols = self.symbols.copy()
        [self.symbols.pop(arg.id, None) for arg in node.args.args]
        node.body = [k for k in (self.visit(n) for n in node.body) if k]
        self.symbols = gsymbols
        return node

    def visit_Assign(self, node):
        new_node = self.generic_visit(node)
        [self.symbols.pop(t.id, None)
         for t in new_node.targets if isinstance(t, ast.Name)]
        return new_node

    def visit_Name(self, node):
        if node.id in self.symbols:
            new_node = reduce(
                lambda v, o: ast.Attribute(v, o, ast.Load()),
                self.symbols[node.id][1:],
                ast.Name(self.symbols[node.id][0], ast.Load())
                )
            new_node.ctx = node.ctx
            ast.copy_location(new_node, node)
            return new_node
        return node
