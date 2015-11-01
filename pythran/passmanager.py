"""
This module provides classes and functions for pass management.

There are two kinds of passes: transformations and analysis.
    * ModuleAnalysis, FunctionAnalysis and NodeAnalysis are to be
      subclassed by any pass that collects information about the AST.
    * gather is used to gather (!) the result of an analyses on an AST node.
    * Backend is to be sub-classed by any pass that dumps the AST content.
    * dump is used to dump (!) the AST using the given backend.
    * Transformation is to be sub-classed by any pass that updates the AST.
    * apply is used to apply (sic) a transformation on an AST node.
"""

import ast
import re


def uncamel(name):
    """Transform CamelCase naming convention into C-ish convention."""
    s1 = re.sub('(.)([A-Z][a-z]+)', r'\1_\2', name)
    return re.sub('([a-z0-9])([A-Z])', r'\1_\2', s1).lower()


class AnalysisContext(object):

    """
    Class that stores the hierarchy of node visited.

    Contains:
        * parent module
        * parent function
    """

    def __init__(self):
        self.module = None
        self.function = None


class ContextManager(object):

    """
    Class to be inherited from to add automatic update of context.

    The optional analysis dependencies are listed in `dependencies'.
    """

    def __init__(self, *dependencies):
        """ Create default context and save all dependencies. """
        self.deps = dependencies
        self.verify_dependencies()
        self.ctx = AnalysisContext()
        super(ContextManager, self).__init__()

    def verify_dependencies(self):
        """
        Checks no analysis are called before a transformation,
        as the transformation could invalidate the analysis.
        """

        for i in range(1, len(self.deps)):
            assert(not (isinstance(self.deps[i], Transformation) and
                   isinstance(self.deps[i - 1], Analysis))
                   ), "invalid dep order for %s" % self

    def visit(self, node):
        if isinstance(node, ast.Module):
            self.ctx.module = node
        elif isinstance(node, ast.FunctionDef):
            self.ctx.function = node
            for D in self.deps:
                if issubclass(D, FunctionAnalysis):
                    key = D, node
                    if key not in self.passmanager._cache:
                        d = D()
                        d.passmanager = self.passmanager
                        d.ctx = self.ctx
                        self.passmanager._cache[key] = d.run(node, self.ctx)
                    setattr(self, uncamel(D.__name__),
                            self.passmanager._cache[key])
        return super(ContextManager, self).visit(node)

    def prepare(self, node, ctx):
        '''Gather analysis result required by this analysis'''
        if not self.ctx.module and ctx and ctx.module:
            self.ctx.module = ctx.module
        if not self.ctx.function and ctx and ctx.function:
            self.ctx.function = ctx.function
        for D in self.deps:
            if issubclass(D, ModuleAnalysis):
                rnode = node if isinstance(node, ast.Module) else ctx.module
            elif issubclass(D, FunctionAnalysis):
                if ctx and ctx.function:
                    rnode = ctx.function
                else:
                    continue
            else:
                rnode = node
            key = node, D
            if key in self.passmanager._cache:
                result = self.passmanager._cache[key]
            else:
                d = D()
                d.passmanager = self.passmanager
                result = d.run(rnode, ctx)
                if getattr(d, 'update', False):
                    self.passmanager._cache.clear()
                else:
                    self.passmanager._cache[key] = result
            setattr(self, uncamel(D.__name__), result)

    def run(self, node, ctx):
        """Override this to add special pre or post processing handlers."""
        self.prepare(node, ctx)
        return self.visit(node)


class Analysis(ContextManager, ast.NodeVisitor):
    """
    A pass that does not change its content but gathers informations about it.
    """
    def __init__(self, *dependencies):
        '''`dependencies' holds the type of all analysis required by this
            analysis. `self.result' must be set prior to calling this
            constructor.'''
        assert hasattr(self, "result"), (
            "An analysis must have a result attribute when initialized")
        ContextManager.__init__(self, *dependencies)

    def run(self, node, ctx):
        super(Analysis, self).run(node, ctx)
        return self.result

    def display(self, data):
        print(data)

    def apply(self, node, ctx):
        self.display(self.run(node, ctx))


class ModuleAnalysis(Analysis):

    """An analysis that operates on a whole module."""


class FunctionAnalysis(Analysis):

    """An analysis that operates on a function."""


class NodeAnalysis(Analysis):

    """An analysis that operates on any node."""


class Backend(ModuleAnalysis):

    """A pass that produces code from an AST."""


class Transformation(ContextManager, ast.NodeTransformer):

    """A pass that updates its content."""

    def __init__(self, *args, **kwargs):
        """ Initialize the update used to know if update happened. """
        super(Transformation, self).__init__(*args, **kwargs)
        self.update = False

    def run(self, node, ctx):
        """ Apply transformation and dependencies and fix new node location."""
        n = super(Transformation, self).run(node, ctx)
        ast.fix_missing_locations(n)
        return n

    def apply(self, node, ctx):
        """ Apply transformation and return if an update happened. """
        new_node = self.run(node, ctx)
        return self.update, new_node


class PassManager(object):
    '''
    Front end to the pythran pass system.
    '''
    def __init__(self, module_name):
        self.module_name = module_name
        self._cache = {}

    def gather(self, analysis, node, ctx=None):
        '''High-level function to call an `analysis' on a `node', eventually
        using a `ctx'.'''
        assert issubclass(analysis, Analysis)
        a = analysis()
        a.passmanager = self
        return a.run(node, ctx)

    def dump(self, backend, node):
        '''High-level function to call a `backend' on a `node' to generate
        code for module `module_name'.'''
        assert issubclass(backend, Backend)
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
        assert issubclass(transformation, (Transformation, Analysis))
        a = transformation()
        a.passmanager = self
        res = a.apply(node, ctx)

        # the transformation updated the AST, so analyse may need to be rerun
        # we could use a finer-grain caching system, and provide a way to flag
        # some analyses as `unmodified' by the transformation, as done in LLVM
        # (and PIPS ;-)
        if a.update:
            self._cache.clear()
        return res
