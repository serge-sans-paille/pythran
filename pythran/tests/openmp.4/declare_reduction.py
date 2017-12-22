#from https://software.intel.com/en-us/node/695675

def min_abs(omp_in, omp_out):
    return min(abs(omp_in), omp_out)

import numpy as np
def find_min_abs(data):
    '''return the smallest magnitude among all the integers in data[N]'''
    result = abs(data[0])
    #omp declare reduction(minabs : int : omp_out = min_abs(omp_in, omp_out)) initializer(omp_priv=omp_orig)

    #omp parallel for reduction(minabs: result)
    for d in data:
        if abs(d) < result:
            result = abs(d)
    return result

def declare_reduction():
    data = [-1, 2, 3, 1, 4, 5, 6, -7]
    res = find_min_abs(data)
    return res == 1
