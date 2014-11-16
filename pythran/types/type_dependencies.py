
import ast
import itertools
from numpy import ndarray

import networkx as nx

from pythran.analyses import GlobalDeclarations
from pythran.passmanager import ModuleAnalysis
from pythran.types.conversion import PYTYPE_TO_CTYPE_TABLE


def pytype_to_deps(t):
    """python -> pythonic type include."""
    if isinstance(t, list):
        return {'pythonic/types/list.hpp'}.union(pytype_to_deps(t[0]))
    elif isinstance(t, set):
        return {'pythonic/types/set.hpp'}.union(pytype_to_deps(list(t)[0]))
    elif isinstance(t, dict):
        tkey, tvalue = t.items()[0]
        return {'pythonic/types/dict.hpp'}.union(pytype_to_deps(tkey),
                                                 pytype_to_deps(tvalue))
    elif isinstance(t, tuple):
        return {'pythonic/types/tuple.hpp'}.union(*map(pytype_to_deps, t))
    elif isinstance(t, ndarray):
        return {'pythonic/types/ndarray.hpp'}.union(pytype_to_deps(t[0]))
    elif t in PYTYPE_TO_CTYPE_TABLE:
        return {'pythonic/types/{}.hpp'.format(t.__name__)}
    else:
        raise NotImplementedError("{0}:{1}".format(type(t), t))


class TypeDependencies(ModuleAnalysis):

    """
    Gathers the callees of each function required for type inference.

    This analyse produces a directed graph with functions as nodes and edges
    between nodes when a function might call another.
    """

    NoDeps = "None"

    def __init__(self):
        self.result = nx.DiGraph()
        self.current_function = None
        ModuleAnalysis.__init__(self, GlobalDeclarations)

    def prepare(self, node, ctx):
        super(TypeDependencies, self).prepare(node, ctx)
        for v in self.global_declarations.itervalues():
            self.result.add_node(v)
        self.result.add_node(TypeDependencies.NoDeps)

    def visit_any_conditionnal(self, node):
        '''
        Set and restore the in_cond variable whenever a node
        the children of which may not be executed is visited
        '''
        in_cond = self.in_cond
        self.in_cond = True
        self.generic_visit(node)
        self.in_cond = in_cond

    def visit_FunctionDef(self, node):
        assert self.current_function is None
        self.current_function = node
        self.naming = dict()
        self.in_cond = False  # True when we are in a if, while or for
        self.generic_visit(node)
        self.current_function = None

    def visit_Return(self, node):
        '''
        Gather all the function call that led to the creation of the
        returned expression and add an edge to each of this function.

        When visiting an expression, one returns a list of frozensets.  Each
        element of the list is linked to a possible path, each element of a
        frozenset is linked to a dependency.
        '''
        if node.value:
            v = self.visit(node.value)
            for dep_set in v:
                if dep_set:
                    for dep in dep_set:
                        self.result.add_edge(dep, self.current_function)
                else:
                    self.result.add_edge(TypeDependencies.NoDeps,
                                         self.current_function)

    visit_Yield = visit_Return

    def update_naming(self, name, value):
        '''
        Update or renew the name <-> dependencies binding
        depending on the in_cond state
        '''
        if self.in_cond:
            self.naming.setdefault(name, []).extend(value)
        else:
            self.naming[name] = value

    def visit_Assign(self, node):
        v = self.visit(node.value)
        for t in node.targets:
            if isinstance(t, ast.Name):
                self.update_naming(t.id, v)

    def visit_AugAssign(self, node):
        v = self.visit(node.value)
        t = node.target
        if isinstance(t, ast.Name):
            self.update_naming(t.id, v)

    def visit_For(self, node):
        self.naming.update({node.target.id: self.visit(node.iter)})
        self.visit_any_conditionnal(node)

    def visit_BoolOp(self, node):
        return sum((self.visit(value) for value in node.values), [])

    def visit_BinOp(self, node):
        args = map(self.visit, (node.left, node.right))
        return list({frozenset.union(*x) for x in itertools.product(*args)})

    def visit_UnaryOp(self, node):
        return self.visit(node.operand)

    def visit_Lambda(self, node):
        assert False

    def visit_IfExp(self, node):
        return self.visit(node.body) + self.visit(node.orelse)

    def visit_Compare(self, node):
        return [frozenset()]

    def visit_Call(self, node):
        args = map(self.visit, node.args)
        func = self.visit(node.func)
        params = args + [func or []]
        return list({frozenset.union(*p) for p in itertools.product(*params)})

    def visit_Num(self, node):
        return [frozenset()]

    def visit_Str(self, node):
        return [frozenset()]

    def visit_Attribute(self, node):
        return [frozenset()]

    def visit_Subscript(self, node):
        return self.visit(node.value)

    def visit_Name(self, node):
        if node.id in self.naming:
            return self.naming[node.id]
        elif node.id in self.global_declarations:
            return [frozenset([self.global_declarations[node.id]])]
        else:
            return [frozenset()]

    def visit_List(self, node):
        if node.elts:
            return list(set(sum(map(self.visit, node.elts), [])))
        else:
            return [frozenset()]

    visit_Set = visit_List

    def visit_Dict(self, node):
        if node.keys:
            items = node.keys + node.values
            return list(set(sum(map(self.visit, items), [])))
        else:
            return [frozenset()]

    visit_Tuple = visit_List

    def visit_Slice(self, node):
        return [frozenset()]

    def visit_Index(self, node):
        return [frozenset()]

    visit_If = visit_any_conditionnal
    visit_While = visit_any_conditionnal
