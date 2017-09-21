""" Computes the Control Flow Graph of a function. """

from pythran.passmanager import FunctionAnalysis

import gast as ast
import networkx as nx


def is_true_predicate(node):
    # FIXME: there may be more patterns here
    if isinstance(node, ast.Num) and node.n:
        return True
    if isinstance(node, ast.Attribute) and node.attr == 'True':
        return True
    return False


def is_false_predicate(node):
    # FIXME: there may be more patterns here
    if isinstance(node, ast.Num) and not node.n:
        return True
    if isinstance(node, ast.Attribute) and node.attr == 'False':
        return True
    return False


class CFG(FunctionAnalysis):
    """
    Computes the Control Flow Graph of a function.

    The processing of a node yields a pair containing
    * the OUT nodes, to be linked with the IN nodes of the successor
    * the RAISE nodes, nodes that stop the control flow (exception/break/...)
    """

    #: The sink node in the control flow graph.
    #:
    #: The predecessors of this node are those AST nodes that terminate
    #: control flow without a return statement.
    NIL = object()

    def __init__(self):
        self.result = nx.DiGraph()
        super(CFG, self).__init__()

    def visit_FunctionDef(self, node):
        # the function itself is the entry point
        self.result.add_node(node)
        currs = (node,)
        for n in node.body:
            self.result.add_node(n)
            for curr in currs:
                self.result.add_edge(curr, n)
            currs, _ = self.visit(n)
        # add an edge to NIL for nodes that end the control flow
        # without a return
        self.result.add_node(CFG.NIL)
        for curr in currs:
            self.result.add_edge(curr, CFG.NIL)

    def visit_Pass(self, node):
        """OUT = node, RAISES = ()"""
        return (node,), ()

    # All these nodes have the same behavior as pass
    visit_Assign = visit_AugAssign = visit_Import = visit_Pass
    visit_Expr = visit_Print = visit_ImportFrom = visit_Pass
    visit_Yield = visit_Delete = visit_Pass

    def visit_Return(self, _):
        """OUT = (), RAISES = ()"""
        return (), ()

    def visit_For(self, node):
        """
        OUT = (node,) + last body statements
        RAISES = body's that are not break or continue
        """
        currs = (node,)
        break_currs = tuple()
        raises = ()
        # handle body
        for n in node.body:
            self.result.add_node(n)
            for curr in currs:
                self.result.add_edge(curr, n)
            currs, nraises = self.visit(n)
            for nraise in nraises:
                if isinstance(nraise, ast.Break):
                    break_currs += (nraise,)
                elif isinstance(nraise, ast.Continue):
                    self.result.add_edge(nraise, node)
                else:
                    raises += (nraise,)
        # add the backward loop
        for curr in currs:
            self.result.add_edge(curr, node)
        # the else statement if needed
        if node.orelse:
            for n in node.orelse:
                self.result.add_node(n)
                for curr in currs:
                    self.result.add_edge(curr, n)
                currs, nraises = self.visit(n)
        # while only
        if hasattr(node, 'test') and is_true_predicate(node.test):
            return break_currs, raises

        return break_currs + currs, raises

    visit_While = visit_For

    def visit_If(self, node):
        """
        OUT = true branch U false branch
        RAISES = true branch U false branch
        """
        currs = (node,)
        raises = ()

        # true branch
        for n in node.body:
            self.result.add_node(n)
            for curr in currs:
                self.result.add_edge(curr, n)
            currs, nraises = self.visit(n)
            raises += nraises
        if is_true_predicate(node.test):
            return currs, raises

        # false branch
        tcurrs = currs
        currs = (node,)
        for n in node.orelse:
            self.result.add_node(n)
            for curr in currs:
                self.result.add_edge(curr, n)
            currs, nraises = self.visit(n)
            raises += nraises
        return tcurrs + currs, raises

    def visit_Raise(self, node):
        """OUT = (), RAISES = (node)"""
        return (), (node,)

    visit_Break = visit_Continue = visit_Raise

    def visit_Assert(self, node):
        """OUT = RAISES = (node)"""
        if is_false_predicate(node.test):
            return (), (node, )
        else:
            return (node,), (node,)

    def visit_Try(self, node):
        """
        OUT = body's U handler's
        RAISES = handler's
        this equation is not has good has it could be...
        but we need type information to be more accurate
        """
        currs = (node,)
        raises = ()
        for handler in node.handlers:
            self.result.add_node(handler)
        for n in node.body:
            self.result.add_node(n)
            for curr in currs:
                self.result.add_edge(curr, n)
            currs, nraises = self.visit(n)
            for nraise in nraises:
                if isinstance(nraise, ast.Raise):
                    for handler in node.handlers:
                        self.result.add_edge(nraise, handler)
                else:
                    raises += (nraise,)
        for handler in node.handlers:
            ncurrs, nraises = self.visit(handler)
            currs += ncurrs
            raises += nraises
        return currs, raises

    def visit_ExceptHandler(self, node):
        """OUT = body's, RAISES = body's"""
        currs = (node,)
        raises = ()
        for n in node.body:
            self.result.add_node(n)
            for curr in currs:
                self.result.add_edge(curr, n)
            currs, nraises = self.visit(n)
            raises += nraises
        return currs, raises
