""" Replaces identities of binary operators """

from pythran.passmanager import Transformation
from pythran.analyses.ast_matcher import ASTMatcher, AST_any

import gast as ast


class BinOpIdentities(Transformation):

    """
    Replaces identities of binary operators

    >>> import gast as ast
    >>> from pythran import passmanager, backend
    >>> from pythran.optimizations import BinOpIdentities
    >>> node = ast.parse('b = a * 0')
    >>> pm = passmanager.PassManager("test")
    >>> _, node = pm.apply(BinOpIdentities, node)
    >>> print(pm.dump(backend.Python, node))
    b = 0
    >>> node = ast.parse('b = a * 1')
    >>> pm = passmanager.PassManager("test")
    >>> _, node = pm.apply(BinOpIdentities, node)
    >>> print(pm.dump(backend.Python, node))
    b = a
    """

    """ 
    Identites for binary operators are implemented as:
      IDs[ast.OPERATION.__name__] = ( ( A, B, C) )
    i.e
      ast.BinOp(left=A, op=OPERATION(), right=B) is replaced with C

    A or B can be AST_any(). 
    If C is AST_any(), then the node will be replaced with node.left
    or node.right depending if A or B was AST_any(), respectively.

    The implemented identities are
       x * 0 = 0
       0 * x = 0
       x * 1 = x
       1 * x = x
       x + 0 = x
       0 + x = x
       x - 0 = x
    """
    IDs = {}
    IDs[ast.Mult.__name__] = ( (ast.Num(0), AST_any(), ast.Num(0)),
                               (AST_any(), ast.Num(0), ast.Num(0)),
                               (AST_any(), ast.Num(1), AST_any()),
                               (ast.Num(1), AST_any(), AST_any()), )

    IDs[ast.Add.__name__] = ( (ast.Num(0), AST_any(), AST_any()),
                              (AST_any(), ast.Num(0), AST_any()), )

    IDs[ast.Sub.__name__] = ( (AST_any(), ast.Num(0), AST_any()), )

    def __init__(self):
        Transformation.__init__(self)
        
    def visit_BinOp(self, node):
        self.generic_visit(node)
        if node.op.__class__.__name__ in self.IDs:
            for identity in self.IDs[node.op.__class__.__name__]:
                if ASTMatcher(ast.BinOp(identity[0], node.op, identity[1])).search(node):
                    replace = identity[2]
                    if isinstance(replace, AST_any):
                        if isinstance(identity[0], AST_any) and isinstance(identity[1], AST_any):
                            print("Error: identity (AST_any(), AST_any(), AST_any()) not allowed.")
                            replace = node
                        elif isinstance(identity[0], AST_any):
                            replace = node.left
                        elif isinstance(identity[1], AST_any):
                            replace = node.right
                    #print("Replacing ", ast.dump(node), " with ", ast.dump(replace))
                    ast.copy_location(replace, node)
                    return replace
        return node
