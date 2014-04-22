"""
NormalizeIdentifiers prevents conflicts with c++ keywords
"""
import ast
from pythran.analyses import Identifiers
from pythran.passmanager import Transformation
from pythran.tables import cxx_keywords


class NormalizeIdentifiers(Transformation):
    '''
    Prevents naming conflict with c++ keywords by appending extra '_'
    to conflicting names.

    >>> import ast, passmanager, backend
    >>> node = ast.parse("def namespace(union):pass")
    >>> pm = passmanager.PassManager("test")
    >>> d = pm.apply(NormalizeIdentifiers, node)
    >>> print pm.dump(backend.Python, node)
    def namespace_(union_):
        pass
    '''

    def __init__(self):
        self.renamings = dict()
        Transformation.__init__(self, Identifiers)

    def rename(self, name):
        if name not in self.renamings:
            new_name = name
            while new_name in self.identifiers:
                new_name += "_"
            self.renamings[name] = new_name
        return self.renamings[name]

    def run(self, node, ctx):
        super(NormalizeIdentifiers, self).run(node, ctx)
        return self.renamings

    def visit_Name(self, node):
        if node.id in cxx_keywords:
            node.id = self.rename(node.id)
        return node

    def visit_FunctionDef(self, node):
        if node.name in cxx_keywords:
            node.name = self.rename(node.name)
        self.visit(node.args)
        [self.visit(n) for n in node.body]
        return node

    def visit_alias(self, node):
        if node.name in cxx_keywords:
            node.name = self.rename(node.name)
        if node.asname:
            if node.asname in cxx_keywords:
                node.asname = self.rename(node.asname)
        return node

    def visit_ImportFrom(self, node):
        self.generic_visit(node)
        if node.module and node.module in cxx_keywords:
            node.module = self.rename(node.module)
        return node

    def visit_Attribute(self, node):
        self.visit(node.value)
        if node.attr in cxx_keywords:
            node.attr += "_"  # cross fingers
        # Always true as long as we don't have custom classes.
        return node
