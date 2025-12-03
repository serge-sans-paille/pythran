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
    def __init__(self, on=None):
        self.on = on if on is not None else set()

    def walk(self):
        return self.on if isinstance(self.on, set) else self.on.walk()

    def _join(self, s):
        assert self is not s
        if isinstance(self.on, set):
            self.on = s
        else:
            self.on._join(s)

    def join(self, with_):
        if self.walk() is with_.walk():
            return

        # FIXME: reduce walking
        print(self.walk(), "/\\", with_.walk(), end="")
        self_ = self.walk()
        if not self_:
            self_.update(with_.walk())
        else:
            self_.intersection_update(with_.walk())
        with_._join(self)
        print(" =", self.walk())

    def add(self, elt):
        self.on.add(elt)


class PkgEquivalenceClasses(ast.NodeVisitor):
    def __init__(self, duc, udc, ancestors):
        self.duc = duc
        self.udc = udc
        self.ancestors = ancestors
        self.equivalence_classes = defaultdict(SetView)

    def mark_equivalent(self, nodes):
        if not nodes:
            return
        ref_node, nodes = nodes[0], nodes[1:]
        ref_set = self.equivalence_classes[ref_node]
        for value in nodes:
            value_defs = self.udc.chains[value]
            for value_def in value_defs:
                if isinstance(value_def.node, ast.FunctionDef):
                    self.equivalence_classes[ref_node].join(
                        self.equivalence_classes[value_def.node]
                    )
                    self.equivalence_classes[ref_node].add(value_def.node)

    def visit_FunctionDef(self, node):
        callees = self.duc.chains[node]
        for callee in callees.users():
            parent = self.ancestors.parent(callee.node)
            if isinstance(parent, ast.Call):
                if parent.func is callee.node:
                    self.equivalence_classes[node].add(node)
            elif isinstance(parent, (ast.List, ast.Tuple, ast.Set)):
                self.mark_equivalent(parent.elts)
            elif isinstance(parent, ast.Dict):
                if callee.node in parent.keys:
                    self.mark_equivalent(parent.keys)
                else:
                    self.mark_equivalent(parent.values)
            else:
                continue
        self.generic_visit(node)


class LocalAttributeInference(ast.NodeVisitor):
    def __init__(self, pkgs, udc, ancestors, equivalence_classes):
        self.pkgs_description = pkgs
        self.pkg_constraints = defaultdict(lambda: defaultdict(set))
        self.equivalence_classes = equivalence_classes
        self.udc = udc
        self.ancestors = ancestors

    def visit_FunctionDef(self, node):
        if (
            len(self.ancestors.parents(node)) == 1
            and node.name in self.pkgs_description
        ):
            # Only top-level functions can be annotated
            description = self.pkgs_description[node.name]
            for materialized_index, materialized_pkg in description:
                self.pkg_constraints[node][materialized_index] = {(materialized_pkg,)}
        self.generic_visit(node)

    def visit_Attribute(self, node):
        self.generic_visit(node)

        if node.attr in attributes:
            return
        if node.attr in subpackages:
            pkgnames = {p for p, _ in subpackages[node.attr]}
            strict = True
        elif node.attr in functions and isinstance(node.value, ast.Name):
            pkgnames = {p for p, _ in functions.get(node.attr, ())}
        else:
            return

        val_defs = self.udc.chains[node.value]
        if len(val_defs) != 1:
            raise PythranSyntaxError("too many options")
        (val_def,) = val_defs
        val_node = val_def.node
        if not isinstance(val_node, ast.Name) or not isinstance(
            val_node.ctx, ast.Param
        ):
            return
        val_function = self.ancestors.parentFunction(val_node)
        val_index = val_function.args.args.index(val_node)
        for val_function in self.equivalence_classes[val_function].walk():
            constraints = self.pkg_constraints[val_function][val_index]
            if not constraints:
                constraints.update(pkgnames)
            else:
                constraints.intersection_update(pkgnames)
            if not constraints:
                raise PythranSyntaxError("...")


class AttributeResolver(ast.NodeTransformer):
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
    duc = beniget.DefUseChains()
    duc.visit(ir)
    udc = beniget.UseDefChains(duc)
    ancestors = beniget.Ancestors()
    ancestors.visit(ir)

    pec = PkgEquivalenceClasses(duc, udc, ancestors)
    pec.visit(ir)

    inference = LocalAttributeInference(
        pkgs or {}, udc, ancestors, pec.equivalence_classes
    )
    inference.visit(ir)

    resolver = AttributeResolver(inference.pkg_constraints)
    new_ir = resolver.visit(ir)
    return new_ir
