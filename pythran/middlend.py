'''This module turns a python AST into an optimized, pythran compatible ast'''
from passes import remove_comprehension, remove_nested_functions, remove_lambdas, normalize_tuples, normalize_return, normalize_method_calls, normalize_attributes, unshadow_parameters, expand_imports, gather_openmp_data
from analysis import flag_temporaries

def refine(node):
    """refine node in place until it matches pythran's expectations"""
    # parse openmp directive
    gather_openmp_data(node)

    # sanitize input
    normalize_method_calls(node)
    normalize_attributes(node)
    normalize_tuples(node)
    remove_comprehension(node)
    normalize_return(node)
    remove_nested_functions(node)
    remove_lambdas(node)
    expand_imports(node)
    unshadow_parameters(node)

    # some optimizations
    #parallelize_maps(node) # not ready yet...
    flag_temporaries(node)

