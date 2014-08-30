""" Module to looks for a specified pattern in a given AST. """

from ast import AST, iter_fields
from itertools import imap
import ast


class Placeholder(AST):

    """ Class to save information from ast while check for pattern. """

    def __init__(self, identifier):
        """ Placehorder are identified using an identifier. """
        self.id = identifier
        super(Placeholder, self).__init__()


class AST_any(object):

    """ Class to specify we don't care about a field value in ast. """


class AST_or(object):

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


class BaseMatcher(object):

    """
    Matcher to check matching between a pattern.

    It saves information for placeholders.
    """

    def __init__(self):
        """ Basic initialiser declaring placeholders container. """
        self.placeholders = dict()
        super(BaseMatcher, self).__init__()

    def jocker_match(self, (key_n, value_n), (key_p, value_p)):
        """
        Check matching between node and placeholders/Jockers.

        AST_any permit to specify we don't care about a field value while
        AST_or permit to specify multiple possible value for a field value.
        Placeholder have to be always the same and store value.
        """
        if key_n != key_p:
            return False
        elif isinstance(value_p, AST_any):
            # We don't check this field
            return True
        elif isinstance(value_p, AST_or):
            # for AST_or, check for at least one matching pattern
            return any(self.field_match(value_n, value_or)
                       for value_or in value_p.args)
        elif isinstance(value_p, Placeholder):
            if (value_p.id in self.placeholders and
                    not self.field_match(value_n,
                                         self.placeholders[value_p.id])):
                return False
            else:
                self.placeholders[value_p.id] = value_n
                return True
        else:
            return self.field_match(value_n, value_p)

    def match(self, node, pattern):
        """
        Check matching between an ast.Node and a pattern.

        It matchs if node are same are fields are matching too.
        """
        if type(node) != type(pattern):
            return False
        if len(list(iter_fields(node))) != len(list(iter_fields(pattern))):
            return False

        return all(imap(self.jocker_match, iter_fields(node),
                        iter_fields(pattern)))

    def field_match(self, value_n, value_p):
        """ Check for matching between two fields values. """
        if type(value_n) != type(value_p):
            # Type mismatch, so node differ
            return False

        if isinstance(value_n, list):
            return self.list_match(value_n, value_p)
        elif isinstance(value_n, AST):
            return self.match(value_n, value_p)
        else:
            return value_n == value_p

    def list_match(self, node_list, pattern_list):
        """ Check matching between nodes and patterns of ast.Node. """
        if len(node_list) != len(pattern_list):
            return False
        for item_n, item_p in zip(node_list, pattern_list):
            if isinstance(item_p, AST_any):
                continue
            elif isinstance(item_p, Placeholder):
                self.placeholders[item_p.id] = item_n
            elif isinstance(item_n, AST):
                return self.match(item_n, item_p)
            elif item_n != item_p:
                return False
        return True


class ASTMatcher(ast.NodeVisitor, BaseMatcher):

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
        if self.match(node, self.pattern):
            self.result.add(node)
        self.generic_visit(node)

    def search(self, node):
        """ Facility to get values of the matcher for a given node. """
        self.visit(node)
        return self.result
