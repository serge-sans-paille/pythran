""" GlobalEffects computes function effect on global state. """
from __future__ import print_function

from pythran.analyses.aliases import Aliases
from pythran.analyses.global_declarations import GlobalDeclarations
from pythran.passmanager import ModuleAnalysis
from pythran.tables import MODULES
import pythran.intrinsic as intrinsic

import ast
import networkx as nx


class GlobalEffects(ModuleAnalysis):

    """Add a flag on each function that updates a global variable."""

    class FunctionEffect(object):
        def __init__(self, node):
            self.func = node
            if isinstance(node, ast.FunctionDef):
                self.global_effect = False
            elif isinstance(node, intrinsic.Intrinsic):
                self.global_effect = node.global_effects
            elif isinstance(node, ast.alias):
                self.global_effect = False
            elif isinstance(node, str):
                self.global_effect = False
            elif isinstance(node, intrinsic.Class):
                self.global_effect = False
            elif isinstance(node, intrinsic.UnboundValueType):
                self.global_effect = True  # conservative choice
            else:
                print(type(node), node)
                raise NotImplementedError

    def __init__(self):
        self.result = nx.DiGraph()
        self.node_to_functioneffect = dict()
        super(GlobalEffects, self).__init__(Aliases, GlobalDeclarations)

    def prepare(self, node, ctx):
        """
        Initialise globals effects as this analyse is inter-procedural.

        Initialisation done for Pythonic functions and default value set for
        user defined functions.
        """
        super(GlobalEffects, self).prepare(node, ctx)

        def register_node(module):
            """ Recursively save globals effect for all functions. """
            for v in module.itervalues():
                if isinstance(v, dict):  # Submodule case
                    register_node(v)
                else:
                    fe = GlobalEffects.FunctionEffect(v)
                    self.node_to_functioneffect[v] = fe
                    self.result.add_node(fe)
                    if isinstance(v, intrinsic.Class):
                        register_node(v.fields)

        register_node(self.global_declarations)
        for module in MODULES.itervalues():
            register_node(module)
        self.node_to_functioneffect[intrinsic.UnboundValue] = \
            GlobalEffects.FunctionEffect(intrinsic.UnboundValue)

    def run(self, node, ctx):
        super(GlobalEffects, self).run(node, ctx)
        keep_going = True
        while keep_going:
            keep_going = False
            for function in self.result:
                if function.global_effect:
                    for pred in self.result.predecessors(function):
                        if not pred.global_effect:
                            keep_going = pred.global_effect = True
        return {f.func for f in self.result if f.global_effect}

    def visit_FunctionDef(self, node):
        self.current_function = self.node_to_functioneffect[node]
        assert self.current_function in self.result
        self.generic_visit(node)

    def visit_Print(self, _):
        self.current_function.global_effect = True

    def visit_Call(self, node):
        # try to get all aliases of the function, if possible
        # else use [] as a fallback
        func_aliases = self.aliases[node.func]
        # expand argument if any
        func_aliases = reduce(
            lambda x, y: x + (self.node_to_functioneffect.keys()  # all funcs
                              if isinstance(y, ast.Name) else [y]),
            func_aliases,
            list())
        for func_alias in func_aliases:
            # special hook for boundd functions
            if isinstance(func_alias, ast.Call):
                bound_name = func_alias.args[0].id
                func_alias = self.global_declarations[bound_name]
            func_alias = self.node_to_functioneffect[func_alias]
            self.result.add_edge(self.current_function, func_alias)
        self.generic_visit(node)
