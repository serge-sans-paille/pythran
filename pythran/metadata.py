'''This module provides a way to pass information between passes as metadata.
    * add attaches a metadata to a node
    * get retrieves all metadata from a particular class attached to a node
'''
from ast import AST # so that metadata are walkable as regular ast nodes

class Metadata(AST):
    def __init__(self):
        self.data=list()
        self._fields=('data',)
    def __iter__(self): return iter(self.data)
    def append(self, data):self.data.append(data)

class Comprehension(AST):
    def __init__(self, target):
        self.target=target

class NotTemporary(AST):
    pass

class OpenMPDirective(AST):
    default_mode=' default(none)'
    keywords=('omp', 'parallel', 'for', 'shared', 'private', 'reduction', 'default')
    def __init__(self, s):
        class Matcher:
            def __init__(self):
                self.data=list()
            def __call__(self,match):
               if match.group(0) in OpenMPDirective.keywords: return match.group(0)
               else:
                   import ast
                   s= "{"+str(len(self.data))+"}"
                   self.data.append(ast.Name(match.group(0), None))
                   return s
        import re
        m=Matcher()
        self.s=re.sub("\w+", m, s)
        self.deps=m.data
        self._fields=('deps',)

    def __str__(self):
        return self.s.format(*[_.id for _ in self.deps]) 

def add(node, data):
    if not hasattr(node,'metadata'):
        setattr(node,'metadata',Metadata())
        node._fields+=('metadata',)
    getattr(node,'metadata').append(data)

def get(node, class_):
    if hasattr(node,'metadata'):
        return [ s for s in getattr(node,'metadata') if isinstance(s, class_) ]
    else:
        return []
