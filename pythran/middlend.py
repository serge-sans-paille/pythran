"""This module turns a python AST into an optimized, pythran compatible ast."""

from pythran.analyses import ExtendedSyntaxCheck
from pythran.optimizations import ComprehensionPatterns, ListCompToGenexp
from pythran.transformations import (ExpandBuiltins, ExpandImports,
                                     ExpandImportAll, FalsePolymorphism,
                                     NormalizeCompare, NormalizeException,
                                     NormalizeMethodCalls, NormalizeReturn,
                                     NormalizeTuples, RemoveComprehension,
                                     RemoveNestedFunctions, RemoveLambdas,
                                     UnshadowParameters, RemoveNamedArguments,
                                     ExpandGlobals)


def refine(pm, node, optimizations):
    """ Refine node in place until it matches pythran's expectations. """
    # Sanitize input
    pm.apply(ExpandGlobals, node)
    pm.apply(ExpandImportAll, node)
    pm.apply(NormalizeTuples, node)
    pm.apply(ExpandBuiltins, node)
    pm.apply(ExpandImports, node)
    pm.apply(NormalizeException, node)
    pm.apply(NormalizeMethodCalls, node)

    # Some early optimizations
    pm.apply(ComprehensionPatterns, node)

    pm.apply(RemoveLambdas, node)
    pm.apply(RemoveNestedFunctions, node)
    pm.apply(NormalizeCompare, node)

    pm.gather(ExtendedSyntaxCheck, node)

    pm.apply(ListCompToGenexp, node)
    pm.apply(RemoveComprehension, node)
    pm.apply(RemoveNamedArguments, node)

    # sanitize input
    pm.apply(NormalizeReturn, node)
    pm.apply(UnshadowParameters, node)
    pm.apply(FalsePolymorphism, node)

    # some extra optimizations
    apply_optimisation = True
    while apply_optimisation:
        apply_optimisation = False
        for optimization in optimizations:
            apply_optimisation |= pm.apply(optimization, node)[0]
