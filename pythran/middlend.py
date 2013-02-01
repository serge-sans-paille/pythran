'''
This module turns a python AST into an optimized, pythran compatible ast
'''

from passes import RemoveLambdas, NormalizeTuples, NormalizeReturn
from passes import UnshadowParameters, NormalizeException
from passes import NormalizeMethodCalls, NormalizeAttributes, ExpandImports
from passes import SimplifyGenExpIfs
from passes import RemoveComprehension, RemoveNestedFunctions, GatherOMPData

from optimizations import ConstantFolding

default_optimization_sequence = (
        ConstantFolding,
        )


def refine(pm, node, optimizations=default_optimization_sequence):
    """refine node in place until it matches pythran's expectations"""
    # parse openmp directive
    pm.apply(GatherOMPData, node)

    # sanitize input
    pm.apply(NormalizeException, node)
    pm.apply(NormalizeMethodCalls, node)
    pm.apply(NormalizeAttributes, node)
    pm.apply(SimplifyGenExpIfs, node)
    pm.apply(RemoveComprehension, node)
    pm.apply(NormalizeTuples, node)
    pm.apply(RemoveNestedFunctions, node)
    pm.apply(NormalizeReturn, node)
    pm.apply(RemoveLambdas, node)
    pm.apply(ExpandImports, node)
    pm.apply(UnshadowParameters, node)

    # some extra optimizations
    for optimization in optimizations:
        pm.apply(optimization, node)
