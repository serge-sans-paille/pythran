'''
This module turns a python AST into an optimized, pythran compatible ast
'''

from optimizations import GenExpToImap, ListCompToMap, ListCompToGenexp
from transformations import (ExpandBuiltins, ExpandImports, ExpandImportAll,
                             FalsePolymorphism, NormalizeCompare,
                             NormalizeException, NormalizeMethodCalls,
                             NormalizeReturn, NormalizeTuples,
                             RemoveComprehension, RemoveNestedFunctions,
                             RemoveLambdas, UnshadowParameters)


def refine(pm, node, optimizations):
    """refine node in place until it matches pythran's expectations"""

    # sanitize input
    pm.apply(ExpandImportAll, node)
    pm.apply(NormalizeTuples, node)
    pm.apply(ExpandBuiltins, node)
    pm.apply(ExpandImports, node)
    pm.apply(NormalizeException, node)
    pm.apply(NormalizeMethodCalls, node)

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
