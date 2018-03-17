""" Optimization for Python costly pattern. """

from pythran.analyses import Check, Placeholder
from pythran.passmanager import Transformation

import gast as ast


# Tuple of : (pattern, replacement)
# replacement have to be a lambda function to have a new ast to replace when
# replacement is inserted in main ast
know_pattern = [
    # __builtin__.len(__builtin__.set(X)) => __builtin__.pythran.len_set(X)
    (ast.Call(func=ast.Attribute(value=ast.Name(id='__builtin__',
                                                ctx=ast.Load(),
                                                annotation=None),
                                 attr="len", ctx=ast.Load()),
              args=[ast.Call(
                  func=ast.Attribute(
                      value=ast.Name(id='__builtin__',
                                     ctx=ast.Load(), annotation=None),
                      attr="set", ctx=ast.Load()),
                  args=[Placeholder(0)],
                  keywords=[])],
              keywords=[]),
     lambda: ast.Call(
         func=ast.Attribute(
             value=ast.Attribute(value=ast.Name(id='__builtin__',
                                                ctx=ast.Load(),
                                                annotation=None),
                                 attr="pythran", ctx=ast.Load()),
             attr="len_set", ctx=ast.Load()),
         args=[Placeholder(0)], keywords=[])),

    # __builtin__.tuple([X, ..., Z]) => (X, ..., Z)
    (ast.Call(func=ast.Attribute(value=ast.Name(id='__builtin__',
                                                ctx=ast.Load(),
                                                annotation=None),
                                 attr="tuple", ctx=ast.Load()),
              args=[ast.List(Placeholder(0), ast.Load())],
              keywords=[]),
     lambda: ast.Tuple(Placeholder(0), ast.Load())),

    # __builtin__.reversed(__builtin__.xrange(X)) =>
    # __builtin__.xrange(X-1, -1, -1)
    # FIXME : We should do it even when begin/end/step are given
    (ast.Call(func=ast.Attribute(value=ast.Name(id='__builtin__',
                                                ctx=ast.Load(),
                                                annotation=None),
                                 attr="reversed", ctx=ast.Load()),
              args=[ast.Call(
                  func=ast.Attribute(
                      value=ast.Name(id='__builtin__',
                                     ctx=ast.Load(), annotation=None),
                      attr="xrange", ctx=ast.Load()),
                  args=[Placeholder(0)],
                  keywords=[])],
              keywords=[]),
     lambda: ast.Call(
         func=ast.Attribute(value=ast.Name(id='__builtin__',
                                           ctx=ast.Load(), annotation=None),
                            attr="xrange", ctx=ast.Load()),
         args=[ast.BinOp(left=Placeholder(0), op=ast.Sub(),
                         right=ast.Num(n=1)),
               ast.Num(n=-1),
               ast.Num(n=-1)],
         keywords=[])),

    # X * X => X ** 2
    (ast.BinOp(left=Placeholder(0), op=ast.Mult(), right=Placeholder(0)),
     lambda: ast.BinOp(left=Placeholder(0), op=ast.Pow(), right=ast.Num(n=2))),

    # a + "..." + b => "...".join((a, b))
    (ast.BinOp(left=ast.BinOp(left=Placeholder(0),
                              op=ast.Add(),
                              right=ast.Str(Placeholder(1))),
               op=ast.Add(),
               right=Placeholder(2)),
     lambda: ast.Call(func=ast.Attribute(
         ast.Attribute(
             ast.Name('__builtin__', ast.Load(), None),
             'str',
             ast.Load()),
         'join', ast.Load()),
         args=[ast.Str(Placeholder(1)),
               ast.Tuple([Placeholder(0), Placeholder(2)], ast.Load())],
         keywords=[])),
]

# Dictionary with ast operator name as keys for each a list of tuple of
#   (left, right, replacement) is defined.
# replacement have to be a lambda function to have a new ast to replace when
# replacement is inserted in main ast
know_pattern_BinOp = {
    ast.Mult.__name__ : [
        (Placeholder(0), ast.Num(1), lambda: Placeholder(0)), # X * 1 => X
        (ast.Num(1), Placeholder(0), lambda: Placeholder(0)), # 1 * X => X
    ],
    ast.Add.__name__ : [
        (Placeholder(0), ast.Num(0), lambda: Placeholder(0)), # X + 0 => X
        (ast.Num(0), Placeholder(0), lambda: Placeholder(0)), # 0 + X => X
    ],
    ast.Sub.__name__ : [
        (Placeholder(0), ast.Num(0), lambda: Placeholder(0)), # X - 0 => X
        (ast.Num(0), Placeholder(0), lambda: ast.UnaryOp(op=ast.USub(), operand=Placeholder(0))), # 0 - X => -X
    ],
}


class PlaceholderReplace(Transformation):

    """ Helper class to replace the placeholder once value is collected. """

    def __init__(self, placeholders):
        """ Store palceholders value collected. """
        self.placeholders = placeholders
        super(PlaceholderReplace, self).__init__()

    def visit(self, node):
        """ Replace the placeholder if it is one or continue. """
        if isinstance(node, Placeholder):
            return self.placeholders[node.id]
        else:
            return super(PlaceholderReplace, self).visit(node)


class PatternTransform(Transformation):

    """
    Replace all known pattern by pythran function call.

    Based on BaseMatcher to search correct pattern.
    """

    def __init__(self):
        """ Initialize the Basematcher to search for placeholders. """
        super(PatternTransform, self).__init__()

    def visit(self, node):
        """ Try to replace if node match the given pattern or keep going. """
        for pattern, replace in know_pattern:
            check = Check(node, dict())
            if check.visit(pattern):
                node = PlaceholderReplace(check.placeholders).visit(replace())
                self.update = True
        return super(PatternTransform, self).visit(node)

    def visit_BinOp(self, node):
        """ 
        Special method for BinOp.
        Try to replace if node match the given pattern. 
        """
        self.generic_visit(node)
        op_name = node.op.__class__.__name__
        if op_name in know_pattern_BinOp:
            for left, right, replace in know_pattern_BinOp[op_name]:
                check_left = Check(node.left, dict())
                if check_left.visit(left):
                    check_right = Check(node.right, check_left.placeholders)
                    if check_right.visit(right):
                        node = PlaceholderReplace(check_right.placeholders).visit(replace())
                        self.update = True
                        break
        return node
