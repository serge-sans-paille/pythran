"""Insert pythran.denone call after if x is None"""

from pythran.passmanager import Transformation
from pythran.analyses import UseDefChain
import gast as ast


def isnone(node):
    return getattr(node, 'attr', '') == 'None'


class Denone(Transformation):
    """
    Insert pythran.denone call after if x is None test to ease type inference

    >>> import gast as ast
    >>> from pythran import passmanager, backend
    >>> node = ast.parse(\
         "def foo(x):\\n if x is __builtin__.None: x = 1\\n print(x)")
    >>> pm = passmanager.PassManager("test")
    >>> _, node = pm.apply(Denone, node)
    >>> print(pm.dump(backend.Python, node))
    def foo(x):
        if (x is __builtin__.None):
            x = 1
        print(__builtin__.pythran.denone(x))
    """

    def __init__(self):
        super(Denone, self).__init__(UseDefChain)
        self.replacements = set()

    def visit_If(self, node):

        if not isinstance(node.test, ast.Compare):
            return self.generic_visit(node)

        if len(node.test.comparators) != 1:
            return self.generic_visit(node)

        left = node.test.left
        op = node.test.ops[0]
        right = node.test.comparators[0]

        if not isinstance(op, (ast.Is, ast.Eq)):
            return self.generic_visit(node)

        if not isnone(right) and not isnone(left):
            return self.generic_visit(node)

        if isnone(right) and isnone(left):
            return self.generic_visit(node)

        if isnone(left):
            none, value = left, right
        else:
            none, value = right, left

        if not isinstance(value, ast.Name):
            return self.generic_visit(node)

        # insert denone before any use of the tested value
        # this assumes a few things about the usage patterns,
        # but it's generally ok
        G = self.use_def_chain[value.id]
        visited = set()
        to_visit = {n for n in G if G.node[n]['name'] is value}
        while to_visit:
            next_to_visit = set()
            visited.update(to_visit)
            for n in to_visit:
                for s in G.successors(n):
                    if s not in visited:
                        next_to_visit.add(s)
            to_visit.clear()
            next_to_visit, to_visit = to_visit, next_to_visit

        self.replacements.update(G.node[n]['name'] for n in visited
                                 if G.node[n]['name'] is not value)

        return self.generic_visit(node)

    def visit_Name(self, node):
        if node not in self.replacements:
            return node
        if not isinstance(node.ctx, ast.Load):
            return node

        self.update = True

        return ast.Call(
            ast.Attribute(
                ast.Attribute(
                    ast.Name('__builtin__', ast.Load(), None),
                    'pythran',
                    ast.Load()),
                'denone',
                ast.Load()),
            [node],
            []
        )
