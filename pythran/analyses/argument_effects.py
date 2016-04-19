""" ArgumentEffects computes write effect on arguments. """

from pythran.analyses.aliases import Aliases
from pythran.analyses.global_declarations import GlobalDeclarations
from pythran.passmanager import ModuleAnalysis
from pythran.tables import MODULES
import pythran.intrinsic as intrinsic

import ast
import networkx as nx


class FunctionEffects(object):
    def __init__(self, node):
        self.func = node
        if isinstance(node, ast.FunctionDef):
            self.update_effects = [False] * len(node.args.args)
        elif isinstance(node, intrinsic.Intrinsic):
            self.update_effects = [isinstance(x, intrinsic.UpdateEffect)
                                   for x in node.argument_effects]
        elif isinstance(node, ast.alias):
            self.update_effects = []
        elif isinstance(node, intrinsic.Class):
            self.update_effects = []
        else:
            raise NotImplementedError

# Compute the intrinsic effects only once
IntrinsicArgumentEffects = {}


def save_function_effect(module):
    """ Recursively save function effect for pythonic functions. """
    for intr in module.values():
        if isinstance(intr, dict):  # Submodule case
            save_function_effect(intr)
        else:
            fe = FunctionEffects(intr)
            IntrinsicArgumentEffects[intr] = fe
            if isinstance(intr, intrinsic.Class):
                save_function_effect(intr.fields)

for module in MODULES.values():
    save_function_effect(module)


class ArgumentEffects(ModuleAnalysis):

    """Gathers inter-procedural effects on function arguments."""

    def __init__(self):
        self.result = nx.DiGraph()
        self.node_to_functioneffect = IntrinsicArgumentEffects.copy()
        for fe in IntrinsicArgumentEffects.values():
            self.result.add_node(fe)
        super(ArgumentEffects, self).__init__(Aliases, GlobalDeclarations)

    def prepare(self, node, ctx):
        """
        Initialise arguments effects as this analyse is inter-procedural.

        Initialisation done for Pythonic functions and default value set for
        user defined functions.
        """
        super(ArgumentEffects, self).prepare(node, ctx)
        for n in self.global_declarations.values():
            fe = FunctionEffects(n)
            self.node_to_functioneffect[n] = fe
            self.result.add_node(fe)

    def run(self, node, ctx):
        super(ArgumentEffects, self).run(node, ctx)
        keep_going = True  # very naive approach
        while keep_going:
            keep_going = False
            for function in self.result:
                for ue in enumerate(function.update_effects):
                    update_effect_idx, update_effect = ue
                    if not update_effect:
                        continue
                    for pred in self.result.predecessors(function):
                        edge = self.result.edge[pred][function]
                        for fp in enumerate(edge["formal_parameters"]):
                            i, formal_parameter_idx = fp
                            # propagate the impurity backward if needed.
                            # Afterward we may need another graph iteration
                            ith_effectiv = edge["effective_parameters"][i]
                            if(formal_parameter_idx == update_effect_idx and
                               not pred.update_effects[ith_effectiv]):
                                pred.update_effects[ith_effectiv] = True
                                keep_going = True

        return {f.func: f.update_effects for f in self.result}

    def argument_index(self, node):
        while isinstance(node, ast.Subscript):
            node = node.value
        for node_alias in self.aliases[node]:
            if node_alias in self.current_arguments:
                return self.current_arguments[node_alias]
            if node_alias in self.current_subscripted_arguments:
                return self.current_subscripted_arguments[node_alias]
        return -1

    def visit_FunctionDef(self, node):
        self.current_function = self.node_to_functioneffect[node]
        self.current_arguments = {arg: i
                                  for i, arg
                                  in enumerate(node.args.args)}
        self.current_subscripted_arguments = dict()
        assert self.current_function in self.result
        self.generic_visit(node)

    def visit_For(self, node):
        ai = self.argument_index(node.iter)
        if ai >= 0:
            self.current_subscripted_arguments[node.target] = ai
        self.generic_visit(node)

    def visit_AugAssign(self, node):
        n = self.argument_index(node.target)
        if n >= 0:
            self.current_function.update_effects[n] = True
        self.generic_visit(node)

    def visit_Assign(self, node):
        for t in node.targets:
            if isinstance(t, ast.Subscript):
                n = self.argument_index(t)
                if n >= 0:
                    self.current_function.update_effects[n] = True
        self.generic_visit(node)

    def visit_Call(self, node):
        for i, arg in enumerate(node.args):
            n = self.argument_index(arg)
            if n >= 0:
                func_aliases = self.aliases[node.func]

                # pessimistic case: no alias found
                if func_aliases is None:
                    self.current_function.update_effects[n] = True
                    continue

                # expand argument if any
                func_aliases = reduce(
                    lambda x, y: x + (
                        self.node_to_functioneffect.keys()  # all functions
                        if (isinstance(y, ast.Name) and
                            self.argument_index(y) >= 0)
                        else [y]),
                    func_aliases,
                    list())

                for func_alias in func_aliases:
                    # special hook for binded functions
                    if isinstance(func_alias, ast.Call):
                        bound_name = func_alias.args[0].id
                        func_alias = self.global_declarations[bound_name]
                    func_alias = self.node_to_functioneffect[func_alias]
                    predecessors = self.result.predecessors(func_alias)
                    if self.current_function not in predecessors:
                        self.result.add_edge(
                            self.current_function,
                            func_alias,
                            effective_parameters=[],
                            formal_parameters=[])
                    edge = self.result.edge[self.current_function][func_alias]
                    edge["effective_parameters"].append(n)
                    edge["formal_parameters"].append(i)
        self.generic_visit(node)
