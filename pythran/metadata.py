"""
This module provides a way to pass information between passes as metadata.

* add attaches a metadata to a node
* get retrieves all metadata from a particular class attached to a node
"""

from ast import AST  # so that metadata are walkable as regular ast nodes


class Metadata(AST):

    """ Base class to add information on a node to improve code generation. """

    def __init__(self):
        """ Initialize content of these metadata. """
        self.data = list()
        self._fields = ('data',)
        super(Metadata, self).__init__()

    def __iter__(self):
        """ Enable iteration over every metadata informations. """
        return iter(self.data)

    def append(self, data):
        """ Add a metadata information. """
        self.data.append(data)


class Lazy(AST):

    """ Metadata to mark variable which doesn't need to be evaluated now. """


class Comprehension(AST):
    def __init__(self, *args):  # no positional argument to be deep copyable
        super(Comprehension, self).__init__()
        if args:
            self.target = args[0]


class StaticReturn(AST):

    """ Metadata to mark return with a constant value. """


def add(node, data):
    if not hasattr(node, 'metadata'):
        setattr(node, 'metadata', Metadata())
        node._fields += ('metadata',)
    getattr(node, 'metadata').append(data)


def get(node, class_):
    if hasattr(node, 'metadata'):
        return [s for s in getattr(node, 'metadata') if isinstance(s, class_)]
    else:
        return []


def visit(self, node):
    if hasattr(node, 'metadata'):
        self.visit(node.metadata)
