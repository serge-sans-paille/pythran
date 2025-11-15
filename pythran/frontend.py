"""
    This module contains pythran frontend
"""

from pythran.openmp import GatherOMPData
from pythran.syntax import check_syntax
from pythran.tables import pythran_ward
from pythran.transformations import ExtractDocStrings, HandleImport

import gast as ast
import re


def raw_parse(code):
    # hacky way to turn OpenMP comments into strings
    code = re.sub(r'(\s*)#\s*(omp\s[^\n]+)', r'\1"\2"', code)

    return ast.parse(code)

def materialize_pkgs(ir, pkgs):

    class MaterializePkg(ast.NodeTransformer):
        def visit_FunctionDef(self, node):
            if node.name not in pkgs:
                return node
            pkg_renames = [(pkgname, node.args.args[i].id) for i, pkgname in
                           pkgs[node.name]]
            node.body = [ast.Import([ast.alias(*pkgrename)]) for pkgrename in
                                    pkg_renames] + node.body
            for i, _ in pkgs[node.name]:
                node.args.args[i].id = f'{pythran_ward}_ignored_{i}'
            # no recursive call, we cannot export inner functions
            return node

    return MaterializePkg().visit(ir)


def parse(pm, code, pkgs=None):

    # front end
    ir = raw_parse(code)

    # Materialize user-defined pkg arguments, if any
    if pkgs:
        ir = materialize_pkgs(ir, pkgs)

    # Handle user-defined import
    pm.apply(HandleImport, ir)

    # parse openmp directive
    pm.apply(GatherOMPData, ir)

    # extract docstrings
    _, docstrings = pm.apply(ExtractDocStrings, ir)

    # avoid conflicts with cxx keywords
    check_syntax(ir)
    return ir, docstrings
