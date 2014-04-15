"""
Scope computes scope information
"""
import ast
from ancestors import Ancestors
from collections import defaultdict
import pythran.openmp as openmp
from pythran.passmanager import FunctionAnalysis
from use_def_chain import UseDefChain


class Scope(FunctionAnalysis):
    '''
    Associate each variable declaration with the node that defines it

    Whenever possible, associate the variable declaration to an assignment,
    otherwise to a node that defines a bloc (e.g. a For)
    This takes OpenMP information into accounts!
    The result is a dictionary with nodes as key and set of names as values
    '''

    def __init__(self):
        self.result = defaultdict(lambda: set())
        self.decl_holders = (ast.FunctionDef, ast.For,
                             ast.While, ast.TryExcept)
        super(Scope, self).__init__(Ancestors, UseDefChain)

    def visit_OMPDirective(self, node):
        for dep in node.deps:
            if type(dep) is ast.Name:
                self.openmp_deps.setdefault(dep.id, []).append(dep)

    def visit_FunctionDef(self, node):
        # first gather some info about OpenMP declarations
        self.openmp_deps = dict()
        self.generic_visit(node)

        # then compute scope informations
        # unlike use-def chains, this takes OpenMP annotations into account
        for name, udgraph in self.use_def_chain.iteritems():
            # get all refs to that name
            refs = [udgraph.node[n]['name'] for n in udgraph]
            # add OpenMP refs (well, the parent of the holding stmt)
            refs.extend(self.ancestors[d][-3]   # -3 to get the right parent
                        for d in self.openmp_deps.get(name, []))
            # get their ancestors
            ancestors = map(self.ancestors.__getitem__, refs)
            # common ancestors
            prefixes = filter(lambda x: len(set(x)) == 1, zip(*ancestors))
            common = prefixes[-1][0]  # the last common ancestor

            # now try to attach the scope to an assignment.
            # This will be the first assignment found in the bloc
            if type(common) in self.decl_holders:
                # get all refs that define that name
                refs = [udgraph.node[n]['name']
                        for n in udgraph if udgraph.node[n]['action'] == 'D']
                refs.extend(self.openmp_deps.get(name, []))
                # get their parent
                prefs = set()
                for r in refs:
                    if type(self.ancestors[r][-1]) is openmp.OMPDirective:
                        # point to the parent of the stmt holding the metadata
                        prefs.add(self.ancestors[r][-4])
                    else:
                        prefs.add(self.ancestors[r][-1])
                # set the defining statement to the first assign in the body
                # unless another statements uses it before
                # or the common itselfs holds a dependency
                if common not in prefs:
                    for c in common.body:
                        if c in prefs:
                            if type(c) is ast.Assign:
                                common = c
                            break
            self.result[common].add(name)
