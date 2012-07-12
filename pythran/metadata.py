'''This module provides a way to pass information between passes as metadata.
    * add attaches a metadata to a node
    * get retrieves all metadat from a particular class attached to a node
'''

class comprehension(object):
    def __init__(self, target):
        self.target=target


def add(node, data):
    if not hasattr(node,'__metadata__'):
        setattr(node,'__metadata__',set())
    getattr(node,'__metadata__').add(data)

def get(node, class_):
    if hasattr(node,'__metadata__'):
        return [ s for s in getattr(node,'__metadata__') if isinstance(s, class_) ]
    else:
        return []
