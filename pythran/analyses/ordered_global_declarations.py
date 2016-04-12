""" OrderedGlobalDeclarations orders all global functions. """

from pythran.analyses.aliases import StrictAliases
from pythran.analyses.global_declarations import GlobalDeclarations
from pythran.passmanager import ModuleAnalysis

import ast


class OrderedGlobalDeclarations(ModuleAnalysis):
    '''Order all global functions according to their callgraph depth'''
    def __init__(self):
        self.result = dict()
        super(OrderedGlobalDeclarations, self).__init__(
            StrictAliases, GlobalDeclarations)

    def visit_FunctionDef(self, node):
        self.curr = node
        self.result[node] = set()
        self.generic_visit(node)

    def visit_Name(self, node):
        if node in self.strict_aliases:
            for alias in self.strict_aliases[node]:
                if isinstance(alias, ast.FunctionDef):
                    self.result[self.curr].add(alias)
                elif isinstance(alias, ast.Call):  # this is a bind
                    for alias in self.strict_aliases[alias.args[0]]:
                        self.result[self.curr].add(alias)

    def run(self, node, ctx):
        # compute the weight of each function
        # the weight of a function is the number functions it references
        super(OrderedGlobalDeclarations, self).run(node, ctx)
        old_count = -1
        new_count = 0
        # iteratively propagate weights
        while new_count != old_count:
            for v in self.result.itervalues():
                [v.update(self.result[f]) for f in list(v)]
            old_count = new_count
            new_count = reduce(lambda acc, s: acc + len(s),
                               self.result.itervalues(), 0)
        # return functions, the one with the greatest weight first
        return sorted(self.result.iterkeys(), reverse=True,
                      key=lambda s: len(self.result[s]))
