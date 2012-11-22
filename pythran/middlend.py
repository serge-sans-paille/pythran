'''This module turns a python AST into an optimized, pythran compatible ast
'''
from passes import RemoveLambdas, NormalizeTuples, NormalizeReturn
from passes import UnshadowParameters, NormalizeException, ConstantFolding
from passes import NormalizeMethodCalls, NormalizeAttributes, ExpandImports
from passes import RemoveComprehension, RemoveNestedFunctions, GatherOMPData
from passmanager import apply


def refine(node):
    """refine node in place until it matches pythran's expectations"""
    # parse openmp directive
    apply(GatherOMPData, node)

    # sanitize input
    apply(NormalizeException, node)
    apply(NormalizeMethodCalls, node)
    apply(NormalizeAttributes, node)
    apply(NormalizeTuples, node)
    apply(RemoveComprehension, node)
    apply(RemoveNestedFunctions, node)
    apply(NormalizeReturn, node)
    apply(RemoveLambdas, node)
    apply(ExpandImports, node)
    apply(UnshadowParameters, node)

    # some optimizations
    apply(ConstantFolding, node)
