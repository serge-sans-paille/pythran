""" GlobalDeclarations gathers top-level declarations. """

from pythran.passmanager import ModuleAnalysis
from beniget import DefUseChains


class SilentDefUseChains(DefUseChains):

    def unbound_identifier(self, name, node):
        pass


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

    def visit_Module(self, node):
        """ Import module define a new variable name. """
        duc = SilentDefUseChains()
        duc.visit(node)
        self.result = {d.name(): d.node
                       for d in duc.locals[node]}
