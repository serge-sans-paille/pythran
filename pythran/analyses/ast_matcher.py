""" Module to looks for a specified pattern in a given AST. """

from ast import AST, iter_fields
import ast


class AST_no_cond(object):

    """ Class to specify we don't care about a field value in ast. """


def match(node, pattern):
    """
    Check matching between an ast.Node and a pattern.

    AST_no_cond permit to specify we don't care about a field value
    """
    if node.__class__.__name__ != pattern.__class__.__name__:
        return False
    zipped_nodes = zip(iter_fields(node), iter_fields(pattern))
    for (_, value_n), (_, value_p) in zipped_nodes:
        if isinstance(value_p, AST_no_cond):
            # We don't check this field
            continue
        elif type(value_n) != type(value_p):
            # Type mismatch, so node differ
            return False

        bad_list_matching = (isinstance(value_n, list) and
                             not list_matching(value_n, value_p))
        bad_ast_matching = (isinstance(value_n, AST) and
                            not match(value_n, value_p))
        bad_matching = value_n != value_p

        # If values are not matching list, matching ast node or equal value
        # pattern and node differ
        if bad_list_matching and bad_ast_matching and bad_matching:
            return False
    return True


def list_matching(node_list, pattern_list):
    """ Check matching between nodes and patterns of ast.Node. """
    if len(node_list) != len(pattern_list):
        return False
    for item_n, item_p in zip(node_list, pattern_list):
        if isinstance(item_p, AST_no_cond):
            continue
        elif isinstance(item_n, AST) and not match(item_n, item_p):
            return False
        elif item_n != item_p:
            return False
    return True


class ASTMatcher(ast.NodeVisitor):

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
    """

    def __init__(self, pattern):
        """ Basic initialiser saving pattern and initialising result set. """
        self.pattern = pattern
        self.result = set()

    def visit(self, node):
        """
        Visitor looking for matching between current node and pattern.

        If it match, save it but whatever happen, keep going.
        """
        if match(node, self.pattern):
            self.result.add(node)
        self.generic_visit(node)

    def get(self, node):
        """ Facility to get values of the matcher for a given node. """
        self.visit(node)
        return self.result
