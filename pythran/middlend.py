'''
This module turns a python AST into an optimized, pythran compatible ast
'''

from passes import RemoveLambdas, NormalizeTuples, NormalizeReturn
from passes import UnshadowParameters, NormalizeException, ExpandBuiltins
from passes import NormalizeMethodCalls, NormalizeAttributes, FalsePolymorphism
from passes import RemoveComprehension, RemoveNestedFunctions, ExpandImports
from passes import NormalizeCompare
from optimizations import GenExpToImap, ListCompToMap, ListCompToGenexp, Pow2


def refine(pm, node, optimizations):
    """refine node in place until it matches pythran's expectations"""

    # sanitize input
    pm.apply(NormalizeTuples, node)
    pm.apply(ExpandBuiltins, node)
    pm.apply(ExpandImports, node)
    pm.apply(NormalizeException, node)
    pm.apply(NormalizeMethodCalls, node)
    pm.apply(NormalizeAttributes, node)

    #Some early optimizations
    pm.apply(ListCompToMap, node)
    pm.apply(GenExpToImap, node)

    pm.apply(NormalizeTuples, node)
    pm.apply(RemoveLambdas, node)
    pm.apply(NormalizeCompare, node)
    pm.apply(RemoveNestedFunctions, node)
    pm.apply(ListCompToGenexp, node)
    pm.apply(RemoveComprehension, node)

    # sanitize input
    pm.apply(NormalizeTuples, node)
    pm.apply(RemoveNestedFunctions, node)
    pm.apply(NormalizeReturn, node)
    pm.apply(UnshadowParameters, node)
    pm.apply(FalsePolymorphism, node)

    # some extra optimizations
    for optimization in optimizations:
        pm.apply(optimization, node)
