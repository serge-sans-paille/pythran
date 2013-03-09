'''
This module turns a python AST into an optimized, pythran compatible ast
'''

from passes import RemoveLambdas, NormalizeTuples, NormalizeReturn
from passes import UnshadowParameters, NormalizeException, ExpandBuiltins
from passes import NormalizeMethodCalls, NormalizeAttributes, ExpandImports
from passes import RemoveComprehension, RemoveNestedFunctions
from optimizations import GenExpToImap, ListCompToMap, ListCompToGenexp

from optimizations import ConstantFolding, IterTransformation

default_optimization_sequence = (
        ConstantFolding,
        IterTransformation
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
    pm.apply(NormalizeTuples, node)

    #Some optimization
    pm.apply(ListCompToMap, node)
    pm.apply(NormalizeTuples, node)
    pm.apply(RemoveNestedFunctions, node)
    pm.apply(RemoveLambdas, node)
    pm.apply(ListCompToGenexp, node)
    pm.apply(GenExpToImap, node)
    pm.apply(NormalizeTuples, node)

    # sanitize input
    pm.apply(RemoveComprehension, node)
    pm.apply(RemoveNestedFunctions, node)
    pm.apply(NormalizeReturn, node)
    pm.apply(RemoveLambdas, node)
    pm.apply(UnshadowParameters, node)

    # some extra optimizations
    for optimization in optimizations:
        pm.apply(optimization, node)
