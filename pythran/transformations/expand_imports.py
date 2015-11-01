""" ExpandImports replaces imports by their full paths. """

from pythran.passmanager import Transformation
from pythran.utils import path_to_attr

import ast


class ExpandImports(Transformation):

    """
    Expands all imports into full paths.

    Attributes
    ----------
    imports : {str}
        Imported module (python base module name)
    symbols : {str : (str,)}
        Matching between used name and real cxx name.

    Examples
    --------
    >>> import ast
    >>> from pythran import passmanager, backend
    >>> node = ast.parse("from math import cos ; cos(2)")
    >>> pm = passmanager.PassManager("test")
    >>> _, node = pm.apply(ExpandImports, node)
    >>> print pm.dump(backend.Python, node)
    import math
    math.cos(2)
    >>> node = ast.parse("from os.path import join ; join('a', 'b')")
    >>> _, node = pm.apply(ExpandImports, node)
    >>> print pm.dump(backend.Python, node)
    import os
    os.path.join('a', 'b')
    """

    def __init__(self):
        """ Basic initialiser. """
        Transformation.__init__(self)
        self.imports = set()
        self.symbols = dict()

    def visit_Module(self, node):
        """
        Visit the whole module and add all import at the top level.

        >> import numpy.linalg

        Becomes

        >> import numpy

        """
        node.body = [k for k in (self.visit(n) for n in node.body) if k]
        imports = [ast.Import([ast.alias(i, None)]) for i in self.imports]
        node.body = imports + node.body
        ast.fix_missing_locations(node)
        return node

    def visit_Import(self, node):
        """ Register imported modules and usage symbols.  """
        for alias in node.names:
            alias_name = tuple(alias.name.split('.'))
            self.imports.add(alias_name[0])
            self.symbols[alias.asname or alias.name] = alias_name
            self.update = True
        return None

    def visit_ImportFrom(self, node):
        """ Register imported modules and usage symbols.  """
        module_path = tuple(node.module.split('.'))
        self.imports.add(module_path[0])
        for alias in node.names:
            self.symbols[alias.asname or
                         alias.name] = module_path + (alias.name,)
        self.update = True
        return None

    def visit_FunctionDef(self, node):
        """
        Update import context using overwriting name information.

        Examples
        --------
        >> import foo
        >> import bar
        >> def foo(bar):
        >>     print bar

        In this case, neither bar nor foo can be used in the foo function and
        in future function, foo will not be usable.
        """
        self.symbols.pop(node.name, None)
        gsymbols = self.symbols.copy()
        [self.symbols.pop(arg.id, None) for arg in node.args.args]
        node.body = [k for k in (self.visit(n) for n in node.body) if k]
        self.symbols = gsymbols
        return node

    def visit_Assign(self, node):
        """
        Update import context using overwriting name information.

        Examples
        --------
        >> import foo
        >> def bar():
        >>     foo = 2
        >>     print foo

        In this case, foo can't be used after assign.
        """
        new_node = self.generic_visit(node)
        # no problem if targets contains a subscript, it is not a new assign.
        [self.symbols.pop(t.id, None)
         for t in new_node.targets if isinstance(t, ast.Name)]
        return new_node

    def visit_Name(self, node):
        """
        Replace name with full expanded name.

        Examples
        --------
        >> from numpy.linalg import det

        >> det(a)

        Becomes

        >> numpy.linalg.det(a)
        """
        if node.id in self.symbols:
            new_node = path_to_attr(self.symbols[node.id])
            new_node.ctx = node.ctx
            ast.copy_location(new_node, node)
            return new_node
        return node
