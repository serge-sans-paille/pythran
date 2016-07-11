""" UsedDefChain build used-define chains analysis for each variable. """

from pythran.analyses.imported_ids import ImportedIds
from pythran.analyses.globals_analysis import Globals
from pythran.passmanager import FunctionAnalysis
from pythran.syntax import PythranSyntaxError
import pythran.metadata as md

from itertools import product
import ast
import networkx as nx


class UseDefChain(FunctionAnalysis):

    """
    Build use-define chains analysis for each variable.

    This analyse visit ast and build nodes each time it encounters an
    ast.Name node. It is a U (use) node when context is store and D (define)
    when context is Load or Param.
    This node is linked to all previous possible states in the program.
    Multiple state can happen when we use if-else statement, and loop
    can happen too with for and while statement.
    Result is a dictionary which associate a graph to the matching name.
    """

    def __init__(self):
        self.result = dict()
        self.current_node = dict()
        self.use_only = dict()
        self.in_loop = False
        self.break_ = dict()
        self.continue_ = dict()
        super(UseDefChain, self).__init__(Globals)

    def merge_dict_set(self, into_, from_):
        for i in from_:
            if i in into_:
                into_[i].update(from_[i])
            else:
                into_[i] = from_[i]

    def add_loop_edges(self, prev_node):
        self.merge_dict_set(self.continue_, self.current_node)
        for nid in self.continue_:
            if nid in self.result:
                graph = self.result[nid]
            else:
                graph = self.use_only[nid]
            if nid in prev_node and prev_node[nid] != self.continue_[nid]:
                entering_node = [i for j in prev_node[nid]
                                 for i in graph.successors_iter(j)]
            else:
                entering_node = [n for n in graph if graph.in_degree(n) == 0]
            graph.add_edges_from(product(self.continue_[nid],
                                 entering_node))
        self.continue_ = dict()

    def visit_OMPDirective(self, node):
        '''
        omp directive may introduce new variables,
        do the minimal required processing here
        '''
        for dep in node.deps:
            if dep.id not in self.result and dep.id not in self.use_only:
                # this happens when a local variable is explicitly marked
                # as shared etc
                # In that case, it's a define
                self.result[dep.id] = nx.DiGraph()
                self.result[dep.id].add_node("D0", action="D", name=dep)
                self.current_node[dep.id] = set(["D0"])
            else:
                # safe (?) guess: if the variable is already defined,
                # mark it as updated
                last_node = self.current_node[dep.id].pop()
                self.result[dep.id].node[last_node]['action'] = "UD"
                self.current_node[dep.id] = set([last_node])

    def visit_Name(self, node):
        if node.id not in self.result and node.id not in self.use_only:
            if not (isinstance(node.ctx, ast.Store) or
                    isinstance(node.ctx, ast.Param)):
                if node.id not in self.globals:
                    err = "identifier {0} is used before assignment"
                    raise PythranSyntaxError(err.format(node.id), node)
                else:
                    self.use_only[node.id] = nx.DiGraph()
                    self.use_only[node.id].add_node("D0",
                                                    action="D", name=node)
            else:
                self.result[node.id] = nx.DiGraph()
                self.result[node.id].add_node("D0", action="D", name=node)
            self.current_node[node.id] = set(["D0"])
        else:
            if node.id in self.result:
                graph = self.result[node.id]
            else:
                graph = self.use_only[node.id]
            if (isinstance(node.ctx, ast.Store) or
                    isinstance(node.ctx, ast.Param)):
                if node.id in self.use_only:
                    err = ("identifier {0} has a global linkage and can't"
                           "be assigned")
                    raise PythranSyntaxError(err.format(node.id), node)
                node_name = "D{0}".format(len(graph))
                graph.add_node(node_name, action="D", name=node)
            elif isinstance(node.ctx, ast.Load):
                node_name = "U{0}".format(len(graph))
                graph.add_node(node_name, action="U", name=node)
            else:
                return  # Other context are unused and Del is ignored
            prev_nodes = self.current_node.get(node.id, set())
            edges_list = zip(prev_nodes, [node_name] * len(prev_nodes))
            graph.add_edges_from(edges_list)
            self.current_node[node.id] = set([node_name])

    def visit_Assign(self, node):
        md.visit(self, node)
        # in assignation, left expression is compute before the assignation
        # to the right expression
        self.visit(node.value)
        map(self.visit, node.targets)

    def visit_AugAssign(self, node):
        md.visit(self, node)
        self.visit(node.value)
        self.visit(node.target)
        var = node.target
        while isinstance(var, ast.Subscript):
            var = var.value
        if isinstance(var, ast.Name):
            var = var.id
        else:
            err = "AugAssign can't be used on {0}"
            raise PythranSyntaxError(err.format(var), node)
        last_node = self.current_node[var].pop()
        self.result[var].node[last_node]['action'] = "UD"
        self.current_node[var] = set([last_node])

    def visit_If(self, node):
        md.visit(self, node)
        swap = False
        self.visit(node.test)

        # if an identifier is first used in orelse and we are in a loop,
        # we swap orelse and body
        undef = self.passmanager.gather(ImportedIds, node.body, self.ctx)
        if not all(i in self.current_node for i in undef) and self.in_loop:
            node.body, node.orelse = node.orelse, node.body
            swap = True

        # body
        old_node = {i: set(j) for i, j in self.current_node.iteritems()}
        map(self.visit, node.body)

        # orelse
        new_node = self.current_node
        self.current_node = old_node
        map(self.visit, node.orelse)

        if swap:
            node.body, node.orelse = node.orelse, node.body

        # merge result
        self.merge_dict_set(self.current_node, new_node)

    def visit_IfExp(self, node):
        md.visit(self, node)
        swap = False
        self.visit(node.test)

        # if an identifier is first used in orelse and we are in a loop,
        # we swap orelse and body
        undef = self.passmanager.gather(ImportedIds, node.body, self.ctx)
        if undef and self.in_loop:
            node.body, node.orelse = node.orelse, node.body
            swap = True

        # body
        old_node = {i: set(j) for i, j in self.current_node.iteritems()}
        self.visit(node.body)

        # orelse
        new_node = self.current_node
        self.current_node = old_node
        self.visit(node.orelse)

        if swap:
            node.body, node.orelse = node.orelse, node.body

        # merge result
        self.merge_dict_set(self.current_node, new_node)

    def visit_Break(self, node):
        md.visit(self, node)
        self.merge_dict_set(self.break_, self.current_node)

    def visit_Continue(self, node):
        md.visit(self, node)
        self.merge_dict_set(self.continue_, self.current_node)

    def visit_While(self, node):
        md.visit(self, node)
        prev_node = {i: set(j) for i, j in self.current_node.iteritems()}
        self.visit(node.test)
        # body
        self.in_loop = True
        old_node = {i: set(j) for i, j in self.current_node.iteritems()}
        map(self.visit, node.body)
        self.add_loop_edges(prev_node)
        self.in_loop = False

        # orelse
        new_node = self.current_node
        self.merge_dict_set(self.current_node, old_node)
        map(self.visit, node.orelse)

        # merge result
        self.merge_dict_set(self.current_node, new_node)
        self.merge_dict_set(self.current_node, self.break_)
        self.break_ = dict()

    def visit_For(self, node):
        md.visit(self, node)
        self.visit(node.iter)

        # body
        self.in_loop = True
        old_node = {i: set(j) for i, j in self.current_node.iteritems()}
        self.visit(node.target)
        map(self.visit, node.body)
        self.add_loop_edges(old_node)
        self.in_loop = False

        # orelse
        new_node = self.current_node
        self.merge_dict_set(self.current_node, old_node)
        map(self.visit, node.orelse)

        # merge result
        self.merge_dict_set(self.current_node, new_node)
        self.merge_dict_set(self.current_node, self.break_)
        self.break_ = dict()

    def visit_TryExcept(self, node):
        md.visit(self, node)

        # body
        all_node = dict()
        for stmt in node.body:
            self.visit(stmt)
            for k, i in self.current_node.iteritems():
                if k not in all_node:
                    all_node[k] = i
                else:
                    all_node[k].update(i)

        no_except = self.current_node

        # except
        for ex in node.handlers:
            self.current_node = dict(all_node)
            self.visit(ex)

            # merge result
            self.merge_dict_set(no_except, self.current_node)

        self.current_node = no_except

        if node.orelse:
            err = ("orelse should have been removed in previous passes")
            raise PythranSyntaxError(err, node)

    def visit_TryFinally(self, node):
        """ Assert TryFinally node are already removed before use_def_chain."""
        err = ("This node should have been removed in previous passes")
        raise PythranSyntaxError(err, node)
