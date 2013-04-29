'''
This module provides a way to pass information between passes as metadata.
    * add attaches a metadata to a node
    * get retrieves all metadata from a particular class attached to a node
'''

from ast import AST  # so that metadata are walkable as regular ast nodes


class Metadata(AST):
    def __init__(self):
        self.data = list()
        self._fields = ('data',)

    def __iter__(self):
        return iter(self.data)

    def append(self, data):
        self.data.append(data)


class LocalVariable(AST):
    pass


class Attribute(AST):
    pass


class Comprehension(AST):
    def __init__(self, *args):  # no positional argument to be deep copyable
        if args:
            self.target = args[0]


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
