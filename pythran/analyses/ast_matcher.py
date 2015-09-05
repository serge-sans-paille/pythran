""" Module to looks for a specified pattern in a given AST. """

from ast import AST, iter_fields, NodeVisitor, Dict, Set
from itertools import permutations
from math import isnan

MAX_UNORDERED_LENGTH = 10


class DamnTooLongPattern(Exception):

    """ Exception for long dict/set comparison to reduce compile time. """


class Placeholder(AST):

    """ Class to save information from ast while check for pattern. """

    def __init__(self, identifier):
        """ Placehorder are identified using an identifier. """
        self.id = identifier
        super(Placeholder, self).__init__()


class AST_any(AST):

    """ Class to specify we don't care about a field value in ast. """


class AST_or(AST):

    """
    Class to specify multiple possibles value for a given field in ast.

    Attributes
    ----------
    args: [ast field value]
        List of possible value for a field of an ast.
    """

    def __init__(self, *args):
        """ Initialiser to keep track of arguments. """
        self.args = args
        super(AST_or, self).__init__()


class Check(NodeVisitor):

    """
    Checker for ast <-> pattern.

    NodeVisitor is needed for specific behavior checker.

    Attributs
    ---------
    node : AST
        node we want to compare with pattern
    placeholders : [AST]
        list of placeholder value for later comparison or replacement.
    """

    def __init__(self, node, placeholder):
        """ Initialize attributs. """
        self.node = node
        self.placeholders = placeholder

    def check_list(self, node_list, pattern_list):
        """ Check if list of node are equal. """
        if len(node_list) != len(pattern_list):
            return False
        else:
            return all(Check(node_elt,
                             self.placeholders).visit(pattern_list[i])
                       for i, node_elt in enumerate(node_list))

    def visit_Placeholder(self, pattern):
        """
        Save matching node or compare it with the existing one.

        FIXME : What if the new placeholder is a better choice?
        """
        if (pattern.id in self.placeholders and
                not Check(self.node, self.placeholders).visit(
                    self.placeholders[pattern.id])):
            return False
        else:
            self.placeholders[pattern.id] = self.node
            return True

    @staticmethod
    def visit_AST_any(_):
        """ Every node match with it. """
        return True

    def visit_AST_or(self, pattern):
        """ Match if any of the or content match with the other node. """
        return any(self.field_match(self.node, value_or)
                   for value_or in pattern.args)

    def visit_Set(self, pattern):
        """ Set have unordered values. """
        if len(pattern.elts) > MAX_UNORDERED_LENGTH:
            raise DamnTooLongPattern("Pattern for Set is too long")
        return (isinstance(self.node, Set) and
                any(self.check_list(self.node.elts, pattern_elts)
                    for pattern_elts in permutations(pattern.elts)))

    def visit_Dict(self, pattern):
        """ Dict can match with unordered values. """
        if not isinstance(self.node, Dict):
            return False
        if len(pattern.keys) > MAX_UNORDERED_LENGTH:
            raise DamnTooLongPattern("Pattern for Dict is too long")
        for permutation in permutations(xrange(len(self.node.keys))):
            for i, value in enumerate(permutation):
                if not self.field_match(self.node.keys[i],
                                        pattern.keys[value]):
                    break
            else:
                pattern_values = [pattern.values[i] for i in permutation]
                return self.check_list(self.node.values, pattern_values)
        return False

    def field_match(self, node_field, pattern_field):
        """
        Check if two fields match.

        Field match if:
            - If it is a list, all values have to match.
            - If if is a node, recursively check it.
            - Otherwise, check values are equal.
        """
        is_good_list = (isinstance(pattern_field, list) and
                        self.check_list(node_field, pattern_field))
        is_good_node = (isinstance(pattern_field, AST) and
                        Check(node_field,
                              self.placeholders).visit(pattern_field))

        def strict_eq(f0, f1):
            try:
                return f0 == f1 or (isnan(f0) and isnan(f1))
            except TypeError:
                return f0 == f1

        is_same = strict_eq(pattern_field, node_field)
        return is_good_list or is_good_node or is_same

    def generic_visit(self, pattern):
        """
        Check if the pattern match with the checked node.

        a node match if:
            - type match
            - all field match
        """
        return (isinstance(pattern, type(self.node)) and
                all(self.field_match(value, getattr(pattern, field))
                    for field, value in iter_fields(self.node)))


class ASTMatcher(NodeVisitor):

    """
    Visitor to gather node matching with a given pattern.

    Examples
    --------
    >>> import ast
    >>> code = "[(i, j) for i in xrange(a) for j in xrange(b)]"
    >>> pattern = ast.Call(func=ast.Name(id='xrange', ctx=ast.Load()),
    ...                    args=AST_any(), keywords=[],
    ...                    starargs=None, kwargs=None)
    >>> len(ASTMatcher(pattern).search(ast.parse(code)))
    2
    >>> code = "[(i, j) for i in range(a) for j in xrange(b)]"
    >>> pattern = ast.Call(func=ast.Name(id=AST_or('xrange', 'range'),
    ...                                  ctx=ast.Load()),
    ...                    args=AST_any(), keywords=[],
    ...                    starargs=None, kwargs=None)
    >>> len(ASTMatcher(pattern).search(ast.parse(code)))
    2
    >>> code = "{1:2, 3:4}"
    >>> pattern = ast.Dict(keys=[ast.Num(n=3), ast.Num(n=1)],
    ...                    values=[ast.Num(n=4), ast.Num(n=2)])
    >>> len(ASTMatcher(pattern).search(ast.parse(code)))
    1
    >>> code = "{1, 2, 3}"
    >>> pattern = ast.Set(elts=[ast.Num(n=3), ast.Num(n=2), ast.Num(n=1)])
    >>> len(ASTMatcher(pattern).search(ast.parse(code)))
    1
    """

    def __init__(self, pattern):
        """ Basic initialiser saving pattern and initialising result set. """
        self.pattern = pattern
        self.result = set()
        super(ASTMatcher, self).__init__()

    def visit(self, node):
        """
        Visitor looking for matching between current node and pattern.

        If it match, save it but whatever happen, keep going.
        """
        if Check(node, dict()).visit(self.pattern):
            self.result.add(node)
        self.generic_visit(node)

    def search(self, node):
        """ Facility to get values of the matcher for a given node. """
        self.visit(node)
        return self.result
