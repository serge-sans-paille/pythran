""" Movable computes whteher arguments can be std::moved. """

from pythran.passmanager import FunctionAnalysis
from pythran.analyses.cfg import CFG
from pythran.analyses.use_def_chain import DefUseChains
from pythran.analyses.ancestors import Ancestors
from pythran.graph import has_path
import gast as ast


class Movable(FunctionAnalysis):

    """
    Computes which value can be std::moved


    >>> import gast as ast
    >>> from pythran import passmanager, backend
    >>> code = "def foo(a): return builtins.len(a)"
    >>> node = ast.parse(code)
    >>> pm = passmanager.PassManager("test")
    >>> res = pm.gather(Movable, node)
    >>> print(len(res))
    1
    >>> code = "def foo(a): return builtins.len(a), builtins.id(a)"
    >>> node = ast.parse(code)
    >>> pm = passmanager.PassManager("test")
    >>> res = pm.gather(Movable, node)
    >>> print(len(res))
    0
    """

    def __init__(self):
        # map variable with maximum count of use in the programm
        self.result = set()
        super(Movable, self).__init__(DefUseChains, Ancestors, CFG)

    def parent_stmt(self, node):
        for n in reversed(self.ancestors[node]):
            if isinstance(n, ast.stmt):
                return n

    def visit_FunctionDef(self, node):
        # This is a very simple implementation: if we have only one user,
        # that user is movable.
        candidates = self.def_use_chains.locals[node]

        for candidate in candidates:
            users = candidate.users()
            user_stmts = [self.parent_stmt(u.node) for u in users]
            for src_user, src_stmt in zip(users, user_stmts):
                for dst_user, dst_stmt in zip(users, user_stmts):
                    if src_stmt is dst_stmt and dst_user is not src_user:
                        break
                    if has_path(self.cfg, src_stmt, dst_stmt):
                        break
                else:
                    self.result.add(src_user.node)
