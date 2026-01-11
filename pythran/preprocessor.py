"""
This modules contains various preprocessing passes before any other transformations

Those transformation are applied for any backend
"""

import beniget
import gast as ast
from collections import defaultdict

from pythran.tables import attributes, functions, methods, subpackages
from pythran.syntax import PythranSyntaxError


class SetView:
    """
    Joinable views on a set. The view can be owning or not-owning.

    >>> s0, s1 = SetView({0}), SetView()
    >>> bool(s0), bool(s1)
    (True, False)
    >>> s1.add(1)
    >>> s0
    {0}
    >>> s1
    {1}
    >>> s1.update((0,2))
    >>> s1
    {0, 1, 2}
    >>> s0.join(s1)
    >>> s0
    {0}
    >>> s0._base() is s1._base()
    True
    """
    def __init__(self, on=None):
        self.on = on if on is not None else set()

    def _base(self):
        return self.on if isinstance(self.on, set) else self.on._base()

    def _join(self, s):
        assert self is not s
        if isinstance(self.on, set):
            self.on = s
        else:
            self.on._join(s)

    def join(self, other):
        if self._base() is other._base():
            return
        other._join(self)

    # set interface

    def add(self, elt):
        self.on.add(elt)

    def update(self, values):
        self.on.update(values)

    def intersection_update(self, values):
        self.on.intersection_update(values)

    def __len__(self):
        return len(self.on)

    def __contains__(self, value):
        return value in self.on

    def __repr__(self):
        return repr(self.on)

    def __str__(self):
        return str(self.on)

    def __iter__(self):
        return iter(self.on)


class FunctionsEquivalenceClasses(ast.NodeVisitor):
    '''
    Compute equivalence classes for functions.

    Functions are equivalent if at some point they belong to the same collection, are
    returned from the same if-expression etc.

    This would greatly benefit from a more academic approach, probably in the
    spirit of https://en.wikipedia.org/wiki/Hindley%E2%80%93Milner_type_system

    >>> code = 'def foo(x): pass\\ndef bar(x): pass; y = [foo, bar]'
    >>> ir = ast.parse(code)
    >>> duc = beniget.DefUseChains(); duc.visit(ir)
    >>> udc = beniget.UseDefChains(duc)
    >>> ancestors = beniget.Ancestors() ; ancestors.visit(ir)
    >>> pec = FunctionsEquivalenceClasses(duc, udc, ancestors); pec.visit(ir)
    >>> len(pec.equivalence_classes)
    2
    >>> [f.name for f in pec.equivalence_classes.keys()]
    ['foo', 'bar']
    >>> [(k.name, sorted([v.name for v in vs])) for k, vs in pec.equivalence_classes.items()]
    [('foo', ['bar', 'foo']), ('bar', ['bar', 'foo'])]

    >>> code = 'def foo(x): pass\\ndef bar(x): pass; y = foo if 1 else bar'
    >>> ir = ast.parse(code)
    >>> duc = beniget.DefUseChains(); duc.visit(ir)
    >>> udc = beniget.UseDefChains(duc)
    >>> ancestors = beniget.Ancestors() ; ancestors.visit(ir)
    >>> pec = FunctionsEquivalenceClasses(duc, udc, ancestors); pec.visit(ir)
    >>> len(pec.equivalence_classes)
    2
    >>> [f.name for f in pec.equivalence_classes.keys()]
    ['foo', 'bar']
    >>> [(k.name, sorted([v.name for v in vs])) for k, vs in pec.equivalence_classes.items()]
    [('foo', ['bar', 'foo']), ('bar', ['bar', 'foo'])]

    >>> code = 'def foo(x): pass\\ndef bar(x): pass\\nif 1: x = foo\\nelse: x = bar\\nx(1)'
    >>> ir = ast.parse(code)
    >>> duc = beniget.DefUseChains(); duc.visit(ir)
    >>> udc = beniget.UseDefChains(duc)
    >>> ancestors = beniget.Ancestors() ; ancestors.visit(ir)
    >>> pec = FunctionsEquivalenceClasses(duc, udc, ancestors); pec.visit(ir)
    >>> len(pec.equivalence_classes)
    2
    >>> [f.name for f in pec.equivalence_classes.keys()]
    ['foo', 'bar']
    >>> [(k.name, sorted([v.name for v in vs])) for k, vs in pec.equivalence_classes.items()]
    [('foo', ['bar', 'foo']), ('bar', ['bar', 'foo'])]
    '''
    def __init__(self, duc, udc, ancestors):
        self.duc = duc
        self.udc = udc
        self.ancestors = ancestors
        self.equivalence_classes = defaultdict(SetView)

    def mark_equivalent(self, nodes):
        if not nodes:
            return
        ref_node, nodes = nodes[0], nodes[1:]
        ref_defs = self.udc.chains[ref_node]
        for ref_def in ref_defs:
            if not isinstance(ref_def.node, ast.FunctionDef):
                continue
            for value in nodes:
                value_defs = self.udc.chains[value]
                for value_def in value_defs:
                    if not isinstance(value_def.node, ast.FunctionDef):
                        continue
                    if not self.equivalence_classes[ref_def.node]:
                        self.equivalence_classes[ref_def.node].update(self.equivalence_classes[value_def.node])
                    else:
                        self.equivalence_classes[ref_def.node].intersection_update(self.equivalence_classes[value_def.node])
                    self.equivalence_classes[ref_def.node].join(
                        self.equivalence_classes[value_def.node]
                    )
                    self.equivalence_classes[ref_def.node].add(value_def.node)
                    self.equivalence_classes[ref_def.node].add(ref_def.node)

    def visit_FunctionDef(self, node):
        self.equivalence_classes[node].add(node)
        callees = self.duc.chains[node]

        for callee in callees.users():
            parent = self.ancestors.parent(callee.node)
            if isinstance(parent, ast.IfExp):
                branches = (parent.body, parent.orelse)
                if callee.node in branches:
                    self.mark_equivalent(branches)
            elif isinstance(parent, (ast.List, ast.Tuple, ast.Set)):
                self.mark_equivalent(parent.elts)
            elif isinstance(parent, ast.Dict):
                if callee.node in parent.keys:
                    self.mark_equivalent(parent.keys)
                else:
                    self.mark_equivalent(parent.values)
            elif isinstance(parent, ast.Assign):
                assert callee.node is parent.value
                equivalent_nodes = set()
                for target in parent.targets:
                    if isinstance(target, ast.Name):
                        for user in self.duc.chains[target].users():
                            for def_ in self.udc.chains[user.node]:
                                def_parent = self.ancestors.parent(def_.node)
                                if not isinstance(def_parent, ast.Assign):
                                    continue
                                equivalent_nodes.add(def_parent.value)
                self.mark_equivalent(list(equivalent_nodes))

            else:
                continue
        self.generic_visit(node)


def pretty_constraints(constraints):
    """
    Dump a user-friendly representation of package constraints 
    """
    pretty = []
    for constraint in constraints:
        if isinstance(constraint, tuple):
            pretty.append(".".join(constraint))
        elif isinstance(constraint, ast.Name):
            pretty.append("<instance>")
        else:
            raise NotImplementedError("unknown constraint")
    return ", ".join(pretty)


def haslooseconstraint(constraints):
    """
    Check if the set of constraints contains any loose constraint
    """
    return None in constraints


class LocalAttributeInference(ast.NodeVisitor):
    """
    Gather package constraints applied on attributes
    """

    def __init__(self, pkgs, udc, ancestors, equivalence_classes):
        self.pkgs_description = pkgs
        self.pkg_constraints = defaultdict(lambda: defaultdict(set))
        self.equivalence_classes = equivalence_classes
        self.udc = udc
        self.ancestors = ancestors

    def visit_FunctionDef(self, node):
        istoplevel = len(self.ancestors.parents(node)) == 1
        # Only top-level functions can be annotated
        if istoplevel and node.name in self.pkgs_description:
            description = self.pkgs_description[node.name]
            for materialized_index, materialized_pkg in description:
                self.pkg_constraints[node][materialized_index] = {(materialized_pkg,)}
        self.generic_visit(node)

    def visit_Call(self, node):
        self.generic_visit(node)

        # If a package name is passed as argument, try to resolve the called
        # function and resolve that argument statically. Raise an error if
        # polymorphic packages are used. This could theoretically be supported
        # by Pythran but it currently is not, this would require a new
        # abstraction for packages, something we currently don't have.
        called_functions = [fdef.node for fdef in self.udc.chains[node.func]
                            if isinstance(fdef.node, ast.FunctionDef)]
        if not called_functions:  # cannot compute them statically
            return

        pkg_constraints = set()
        for i, arg in enumerate(node.args):
            for def_ in self.udc.chains.get(arg, ()):
                parent = self.ancestors.parents(def_.node)[-1]
                if isinstance(parent, ast.Import):
                    pkg_constraints.add((i, tuple(def_.node.name.split('.'))))

        for called_function in called_functions:
            for index, pkg in pkg_constraints:
                constraints = self.pkg_constraints[called_function][index]
                if not constraints:
                    constraints.add(pkg)
                else:
                    if pkg not in constraints:
                        raise PythranSyntaxError(
                        "this call allows for package `{}' but other constraints enforce `{}', and those are incompatible".format(
                            pretty_constraints([pkg]), pretty_constraints(constraints)),
                        node
                        )
                    constraints.intersection_update([pkg])



    def visit_Attribute(self, node):
        self.generic_visit(node)
        if node.attr in subpackages:
            pkgnames = {p for p, _ in subpackages[node.attr]}
            strict = True
        elif node.attr in functions and isinstance(node.value, ast.Name):
            pkgnames = {p for p, _ in functions[node.attr]}
        else:
            return

        if node.attr in methods or node.attr in attributes:
            pkgnames.update(p for p, _ in functions.get(node.attr, ()))
            if node.attr in methods:
                pkgnames.add(methods[node.attr][0])  # esp. important for numpy
            # it's a method/attribute, so add an extra candidate which
            # represents the object itself
            pkgnames.add(None)

        # At this point the rhs of the attribute indicates we are attempting to
        # resolve a function call, and the lhs of the attributes indicates that
        # the package of this function call may be dynamic. Walk the definition
        # for this package and register a constraint if we can trace it to a
        # function parameter.
        val_defs = self.udc.chains[node.value]
        for val_def in val_defs:
            val_node = val_def.node
            if not isinstance(val_node, ast.Name) or not isinstance(
                val_node.ctx, ast.Param
            ):
                continue
            callable_node = ast.FunctionDef, ast.Lambda
            val_function = self.ancestors.parentInstance(val_node, callable_node)
            val_index = val_function.args.args.index(val_node)
            for val_function in self.equivalence_classes[val_function]:
                constraints = self.pkg_constraints[val_function][val_index]
                if not constraints:
                    constraints.update(pkgnames)
                else:
                    if constraints.isdisjoint(pkgnames):
                        if haslooseconstraint(pkgnames) or haslooseconstraint(constraints):
                            constraints.add(None)
                            continue
                        raise PythranSyntaxError(
                        "this attribute allows for packages `{}' but other constraints enforce `{}', and those are incompatible".format(
                            pretty_constraints(pkgnames), pretty_constraints(constraints)),
                        node
                        )
                    constraints.intersection_update(pkgnames)


class AttributeResolver(ast.NodeTransformer):
    """
    Based on package constraints, resolve packages when they can be resolved.
    """
    def __init__(self, pkg_constraints):
        self.pkg_constraints = pkg_constraints

    def visit_FunctionDef(self, node):
        self.generic_visit(node)
        extra_imports = sorted(self.pkg_constraints.get(node, {}).items())
        extra_aliases = []
        for i, pkgnames in extra_imports:
            if len(pkgnames) != 1:
                continue
            (pkgname,) = pkgnames
            # FIXME: extra verifications
            (pkg,) = pkgname
            extra_aliases.append(ast.alias(pkg, node.args.args[i].id))
        if extra_aliases:
            node.body.insert(0, ast.Import(extra_aliases))
        return node


def infer_packages(ir, pkgs):
    """
    Using optional package constraints `pkgs`, statically resolve some package names
    on the provided `ir`.
    """
    duc = beniget.DefUseChains()
    duc.visit(ir)
    udc = beniget.UseDefChains(duc)
    ancestors = beniget.Ancestors()
    ancestors.visit(ir)

    pec = FunctionsEquivalenceClasses(duc, udc, ancestors)
    pec.visit(ir)

    inference = LocalAttributeInference(
        pkgs or {}, udc, ancestors, pec.equivalence_classes
    )
    inference.visit(ir)

    resolver = AttributeResolver(inference.pkg_constraints)
    new_ir = resolver.visit(ir)
    return new_ir
