'''
This module provides classes and functions for pass management.
There are two kinds of passes: transformations and analysis.
    * ModuleAnalysis, FunctionAnalysis and NodeAnalysis are to be
      subclassed by any pass that collects information about the AST.
    * gather is used to gather (!) the result of an analyses on an AST node.
    * Backend is to be sub-classed by any pass that dumps the AST content.
    * dump is used to dump (!) the AST using the given backend.
    * Transformation is to be sub-classed by any pass that updates the AST.
    * apply is used to apply (sic) a transformation on an AST node.
'''

import ast
import re


def uncamel(name):
    '''Transforms CamelCase naming convention into C-ish convention'''
    s1 = re.sub('(.)([A-Z][a-z]+)', r'\1_\2', name)
    return re.sub('([a-z0-9])([A-Z])', r'\1_\2', s1).lower()


class AnalysisContext(object):
    '''
    Class that stores the hierarchy of node visited:
        * parent module
        * parent function
    '''
    def __init__(self):
        self.module = None
        self.function = None


class ContextManager(object):
    '''
    Class to be inherited from to add automatic update of
       AnalysisContext `ctx' to a node visitor.
       The optional analysis dependencies are listed in `dependencies'.
    '''
    def __init__(self, *dependencies):
        self.deps = dependencies
        self.ctx = AnalysisContext()

    def visit(self, node):
        if isinstance(node, ast.Module):
            self.ctx.module = node
        elif isinstance(node, ast.FunctionDef):
            self.ctx.function = node
        return super(ContextManager, self).visit(node)

    def run(self, node, ctx):
        '''Gather analysis result required by this analysis and run the
           analysis on `node' using context `context'.'''
        for D in self.deps:
            if issubclass(D, ModuleAnalysis):
                rnode = node if isinstance(node, ast.Module) else ctx.module
            elif issubclass(D, FunctionAnalysis):
                rnode = node if isinstance(node,
                                    ast.FunctionDef) else ctx.function
            else:
                rnode = node
            d = D()
            d.passmanager = self.passmanager
            setattr(self, uncamel(D.__name__), d.run(rnode, ctx))
        return self.run_visit(node)

    def run_visit(self, node):
        '''Override this to add special pre or post processing handlers.'''
        return self.visit(node)


class Analysis(ast.NodeVisitor, ContextManager):
    '''
    A pass that does not change its content but gathers informations
    about it.
    '''
    def __init__(self, *dependencies):
        '''`dependencies' holds the type of all analysis required by this
            analysis. `self.result' must be set prior to calling this
            constructor.'''
        assert hasattr(self, "result"), (
            "An analysis must have a result attribute when initialized")
        ContextManager.__init__(self, *dependencies)

    def run(self, node, ctx):
        ContextManager.run(self, node, ctx)
        return self.result

    def display(self, data):
        print data


class ModuleAnalysis(Analysis):
    '''An analysis that operates on a whole module.'''
    pass


class FunctionAnalysis(Analysis):
    '''An analysis that operates on a function.'''
    pass


class NodeAnalysis(Analysis):
    '''An analysis that operates on any node.'''
    pass


class Backend(ModuleAnalysis):
    '''A pass that produces code from an AST.'''
    pass


class Transformation(ContextManager, ast.NodeTransformer):
    '''A pass that updates its content.'''

    def run_visit(self, node):
        n = super(Transformation, self).run_visit(node)
        ast.fix_missing_locations(n)
        return n


class PassManager(object):
    '''
    Front end to the pythran pass system.
    '''
    def __init__(self, module_name):
        self.module_name = module_name

    def gather(self, analysis, node, ctx=None):
        '''High-level function to call an `analysis' on a `node', eventually
        using a `ctx'.'''
        a = analysis()
        a.passmanager = self
        return a.run(node, ctx)

    def dump(self, backend, node):
        '''High-level function to call a `backend' on a `node' to generate
        code for module `module_name'.'''
        b = backend()
        b.passmanager = self
        return b.run(node, None)

    def apply(self, transformation, node, ctx=None):
        '''
        High-level function to call a `transformation' on a `node',
        eventually using a `ctx'.
        If the transformation is an analysis, the result of the analysis
        is displayed.
        '''
        a = transformation()
        a.passmanager = self
        n = a.run(node, ctx)
        if issubclass(transformation, Analysis):
            a.display(n)
        return n
