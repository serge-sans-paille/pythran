""" GlobalDeclarations gathers top-level declarations. """

from pythran.passmanager import ModuleAnalysis


class GlobalDeclarations(ModuleAnalysis):

    """ Gather all kind of identifier defined at global scope.

    >>> import gast as ast
    >>> from pythran import passmanager
    >>> from pythran.analyses import GlobalDeclarations
    >>> node = ast.parse('''
    ... import math
    ... import math as maths
    ... from math import cos
    ... c = 12
    ... def foo(a):
    ...     b = a + 1''')
    >>> pm = passmanager.PassManager("test")
    >>> sorted(pm.gather(GlobalDeclarations, node).keys())
    ['c', 'cos', 'foo', 'math', 'maths']

    """

    def __init__(self):
        """ Result is an identifier with matching definition. """
        self.result = dict()
        super(GlobalDeclarations, self).__init__()

    def visit_Import(self, node):
        """ Import module define a new variable name. """
        self.result.update((a.asname or a.name, a) for a in node.names)

    def visit_ImportFrom(self, node):
        """ Imported functions define a new variable name. """
        self.result.update((a.asname or a.name, a) for a in node.names)

    def visit_FunctionDef(self, node):
        """ Function definition defined a new identifier. """
        self.result[node.name] = node
        # no generic visit here, so no diving into function body

    def visit_Assign(self, node):
        """ Assigned global variable define a new identifier. """
        for target in node.targets:
            self.result[target.id] = node
