""" Optimization for Python costly pattern. """

from pythran.analyses import BaseMatcher, Placeholder
from pythran.passmanager import Transformation

import ast


# Tuple of : (pattern, replacement)
# replacement have to be a lambda function to have a new ast to replace when
# replacement is inserted in main ast
know_pattern = [
    # __builtin__.len(__builtin__.set(X)) => __builtin__.pythran.len_set(X)
    (ast.Call(func=ast.Attribute(value=ast.Name(id='__builtin__',
                                                ctx=ast.Load()),
                                 attr="len", ctx=ast.Load()),
              args=[ast.Call(
                  func=ast.Attribute(
                      value=ast.Name(id='__builtin__',
                                     ctx=ast.Load()),
                      attr="set", ctx=ast.Load()),
                  args=[Placeholder(0)],
                  keywords=[], starargs=None, kwargs=None)],
              keywords=[], starargs=None, kwargs=None),
     lambda: ast.Call(
         func=ast.Attribute(
             value=ast.Attribute(value=ast.Name(id='__builtin__',
                                                ctx=ast.Load()),
                                 attr="pythran", ctx=ast.Load()),
             attr="len_set", ctx=ast.Load()),
         args=[Placeholder(0)], keywords=[], starargs=None, kwargs=None))]


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


class PatternTransform(BaseMatcher, Transformation):

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
            if self.match(node, pattern):
                node = PlaceholderReplace(self.placeholders).visit(replace())
        return super(PatternTransform, self).visit(node)
