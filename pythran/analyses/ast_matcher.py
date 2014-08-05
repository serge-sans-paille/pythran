""" Module to looks for a specified pattern in a given AST. """

from ast import AST, iter_fields
import ast


class Placeholder(AST):

    """ Class to save information from ast while check for pattern. """

    def __init__(self, identifier):
        """ Placehorder are identified using an identifier. """
        self.id = identifier
        super(Placeholder, self).__init__()


class AST_no_cond(object):

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
    Matcher to check matching between a pattern and a note saving.

    It saves information for placeholders.
    """

    def __init__(self):
        """ Basic initialiser declaring placeholders container. """
        self.placeholders = dict()
        super(BaseMatcher, self).__init__()

    def match(self, node, pattern):
        """
        Check matching between an ast.Node and a pattern.

        AST_no_cond permit to specify we don't care about a field value while
        AST_or permit to specify multiple possible value for a field value.
        """
        if node.__class__.__name__ != pattern.__class__.__name__:
            return False
        zipped_nodes = zip(iter_fields(node), iter_fields(pattern))
        for (_, value_n), (_, value_p) in zipped_nodes:
            if isinstance(value_p, AST_no_cond):
                # We don't check this field
                continue
            elif isinstance(value_p, AST_or):
                # for AST_or, check for at least one matching pattern
                if not any(self.field_matching(value_n, value_or)
                           for value_or in value_p.args):
                    return False
            elif isinstance(value_p, Placeholder):
                self.placeholders[value_p.id] = value_n
            elif not self.field_matching(value_n, value_p):
                return False
        return True

    def field_matching(self, value_n, value_p):
        """ Check for matching between two fields values. """
        if type(value_n) != type(value_p):
            # Type mismatch, so node differ
            return False

        if isinstance(value_n, list):
            return self.list_matching(value_n, value_p)
        elif isinstance(value_n, AST):
            return self.match(value_n, value_p)
        else:
            return value_n == value_p

    def list_matching(self, node_list, pattern_list):
        """ Check matching between nodes and patterns of ast.Node. """
        if len(node_list) != len(pattern_list):
            return False
        for item_n, item_p in zip(node_list, pattern_list):
            if isinstance(item_p, AST_no_cond):
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
    ...                    args=AST_no_cond(), keywords=[],
    ...                    starargs=None, kwargs=None)
    >>> len(ASTMatcher(pattern).get(ast.parse(code)))
    2
    >>> code = "[(i, j) for i in range(a) for j in xrange(b)]"
    >>> pattern = ast.Call(func=ast.Name(id=AST_or('xrange', 'range'),
    ...                                  ctx=ast.Load()),
    ...                    args=AST_no_cond(), keywords=[],
    ...                    starargs=None, kwargs=None)
    >>> len(ASTMatcher(pattern).get(ast.parse(code)))
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

    def get(self, node):
        """ Facility to get values of the matcher for a given node. """
        self.visit(node)
        return self.result
