"""
NodeCount counts the number of nodes in a node
"""
import ast
from pythran.passmanager import NodeAnalysis


class NodeCount(NodeAnalysis):
    """
    Count the number of nodes included in a node

    This has nothing to do with execution time or whatever,
    its mainly use is to prevent the AST from growing too much when unrolling

    >>> import ast, passmanager, backend
    >>> node = ast.parse("if 1: return 3")
    >>> pm = passmanager.PassManager("test")
    >>> print pm.gather(NodeCount, node)
    5
    """

    def __init__(self):
        self.result = 0
        super(NodeCount, self).__init__()

    def generic_visit(self, node):
        self.result += 1
        super(NodeCount, self).generic_visit(node)
