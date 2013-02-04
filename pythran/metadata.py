'''
This module provides a way to pass information between passes as metadata.
    * add attaches a metadata to a node
    * get retrieves all metadata from a particular class attached to a node
'''

from ast import AST  # so that metadata are walkable as regular ast nodes
import ast


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
    def __init__(self, target):
        self.target = target


class OMPDirective(AST):
    default_mode = ' default(none)'
    keywords = ('omp',
        'parallel',
        'for',
        'shared',
        'private',
        'reduction',
        'default',
        'single',
        'nowait',
        'taskwait',
        'task',
        'if',
        'atomic')

    def __init__(self, s):
        class Matcher:
            def __init__(self):
                self.data = list()

            def __call__(self, match):
                if match.group(0) in OMPDirective.keywords:
                    return match.group(0)
                else:
                    s = "{" + str(len(self.data)) + "}"
                    try:
                        v = ast.literal_eval(match.group(0))
                        d = ast.Num(v)
                    except:
                        d = ast.Name(match.group(0), ast.Param())
                    self.data.append(d)
                    return s
        import re
        m = Matcher()
        self.s = re.sub("\w+", m, s)
        self.deps = m.data
        self._fields = ('deps',)

    def __str__(self):
        return self.s.format(
            *[_.id if isinstance(_, ast.Name) else _.n for _ in self.deps])


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
