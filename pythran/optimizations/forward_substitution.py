"""
Replace variable that can be lazy evaluated and used only once by their full
computation code.
"""

from pythran.analyses import LazynessAnalysis, UseDefChain, Literals
from pythran.passmanager import Transformation

import gast as ast


class _LazyRemover(Transformation):
    """
        Helper removing D node and replacing U node by D node assigned value.
        Search value of the D (define) node provided in the constructor (which
        is in an Assign) and replace the U node provided in the constructor too
        by this value.

        Assign Stmt is removed if only one value was assigned.
    """
    def __init__(self, ctx, U, D):
        super(_LazyRemover, self).__init__()
        self.U = U
        self.ctx = ctx
        self.D = D
        self.capture = None

    def visit_Name(self, node):
        if node in self.U:
            return self.capture
        return node

    def visit_Assign(self, node):
        self.generic_visit(node)
        if self.D in node.targets:
            self.capture = node.value
            if len(node.targets) == 1:
                return ast.Pass()
            node.targets.remove(self.D)
        return node


class ForwardSubstitution(Transformation):

    """
    Replace variable that can be compute later.

    >>> import gast as ast
    >>> from pythran import passmanager, backend
    >>> pm = passmanager.PassManager("test")
    >>> node = ast.parse("def foo(): a = [2, 3]; print a")
    >>> _, node = pm.apply(ForwardSubstitution, node)
    >>> print pm.dump(backend.Python, node)
    def foo():
        pass
        print([2, 3])
    >>> node = ast.parse("def foo(): a = 2; print a + a")
    >>> _, node = pm.apply(ForwardSubstitution, node)
    >>> print pm.dump(backend.Python, node)
    def foo():
        pass
        print((2 + 2))
    """

    def __init__(self):
        """ Satisfy dependencies on others analyses. """
        super(ForwardSubstitution, self).__init__(LazynessAnalysis,
                                                  UseDefChain,
                                                  Literals)

    def visit_FunctionDef(self, node):
        """ Forward variable in the function when it is possible. """
        for name, udgraph in self.use_def_chain.items():
            # 1. check if the usedefchains have only two nodes (a def and an
            # use) and if it can be forwarded (lazyness == 1 means variables
            # used to define the variable are not modified and the variable is
            # use only once
            # 2. Check if variable is forwardable and if it is literal
            if ((len(udgraph.nodes()) == 2 and
                 self.lazyness_analysis[name] == 1) or
                    (self.lazyness_analysis[name] != float('inf') and
                     name in self.literals)):
                def get(udgraph, action):
                    """ Return list of used/def variables. """
                    return [udgraph.node[n]['name'] for n in udgraph.nodes()
                            if udgraph.node[n]['action'] == action]
                U = get(udgraph, "U")
                D = get(udgraph, "D")
                # we can't forward if multiple definition for a variable are
                # possible or if this variable is a parameter from a function
                if (len(D) == 1 and len(get(udgraph, "UD")) == 0 and
                        not isinstance(D[0].ctx, ast.Param)):
                    node = _LazyRemover(self.ctx, U, D[0]).visit(node)
                    self.update = True
        return node
