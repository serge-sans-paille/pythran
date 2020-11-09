""" RemoveLambdas turns lambda into regular functions.  """

from pythran.analyses import GlobalDeclarations, ImportedIds
from pythran.passmanager import Transformation
from pythran.tables import MODULES
from pythran.conversion import mangle

import pythran.metadata as metadata

from copy import copy
import gast as ast


class RemoveTypeAnnotations(Transformation):
    """
    Removes type annotations in function and variable
    definitions.

    TODO: add the example
    """

    def __init__(self):
        super(RemoveTypeAnnotations, self).__init__(GlobalDeclarations)

    def visit_FunctionDef(self, node: ast.FunctionDef) -> ast.AST:
        self.generic_visit(node)

        node.returns = None
        for arg in node.args.args:
            arg.annotation = None

        return node

    def visit_AnnAssign(self, node: ast.AnnAssign) -> ast.AST:
        self.generic_visit(node)
        node.value = None
        return node
