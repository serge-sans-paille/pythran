'''
This module turns a python AST into an optimized, pythran compatible ast
'''

from passes import RemoveLambdas, NormalizeTuples, NormalizeReturn
from passes import UnshadowParameters, NormalizeException, ExpandBuiltins
from passes import NormalizeMethodCalls, NormalizeAttributes, FalsePolymorphism
from passes import RemoveComprehension, RemoveNestedFunctions, ExpandImports
from optimizations import GenExpToImap

from optimizations import ConstantFolding

default_optimization_sequence = (
        ConstantFolding,
        )


def refine(pm, node, optimizations=default_optimization_sequence):
    """refine node in place until it matches pythran's expectations"""

    # sanitize input
    pm.apply(NormalizeTuples, node)
    pm.apply(ExpandBuiltins, node)
    pm.apply(ExpandImports, node)
    pm.apply(NormalizeException, node)
    pm.apply(NormalizeMethodCalls, node)
    pm.apply(NormalizeAttributes, node)
    pm.apply(GenExpToImap, node)
    pm.apply(NormalizeTuples, node)
    pm.apply(RemoveComprehension, node)
    pm.apply(NormalizeTuples, node)
    pm.apply(RemoveNestedFunctions, node)
    pm.apply(NormalizeReturn, node)
    pm.apply(RemoveLambdas, node)
    pm.apply(UnshadowParameters, node)
    pm.apply(FalsePolymorphism, node)

    # some extra optimizations
    for optimization in optimizations:
        pm.apply(optimization, node)
