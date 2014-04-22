"""
IterTransformation replaces expressions by iterators when possible.
"""
import ast
from pythran.analyses import PotentialIterator, Aliases
from pythran.passmanager import Transformation
from pythran.tables import equivalent_iterators


class IterTransformation(Transformation):
    '''
    Replaces expressions by iterators when possible.

    >>> import ast, passmanager, backend
    >>> node = ast.parse("""                      \\n\
def foo(l):                                       \\n\
    return __builtin__.sum(l)                     \\n\
def bar(n):                                       \\n\
    return foo(__builtin__.range(n)) \
""")
    >>> pm = passmanager.PassManager("test")
    >>> node = pm.apply(IterTransformation, node)
    >>> print pm.dump(backend.Python, node)
    import itertools
    def foo(l):
        return __builtin__.sum(l)
    def bar(n):
        return foo(__builtin__.xrange(n))
    '''
    def __init__(self):
        Transformation.__init__(self, PotentialIterator, Aliases)

    def find_matching_builtin(self, node):
        if node.func in self.aliases:
            for k, v in self.aliases.iteritems():
                if (isinstance(k, ast.Attribute)
                        and isinstance(k.value, ast.Name)):
                    if k.value.id == "__builtin__":
                        if self.aliases[node.func].aliases == v.aliases:
                            return k.attr

    def visit_Module(self, node):
        self.generic_visit(node)
        importIt = ast.Import(names=[ast.alias(name='itertools', asname=None)])
        return ast.Module(body=([importIt] + node.body))

    def visit_Call(self, node):
        if node in self.potential_iterator:
            f = self.find_matching_builtin(node)
            if f in equivalent_iterators:
                (ns, new) = equivalent_iterators[f]
                node.func = ast.Attribute(
                    value=ast.Name(id=ns, ctx=ast.Load()),
                    attr=new, ctx=ast.Load())
        return self.generic_visit(node)
