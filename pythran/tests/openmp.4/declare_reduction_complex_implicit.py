import numpy as np
def csum(data):
    result = 0.
    #omp parallel for reduction(+: result)
    for d in data:
        result += d
    return result

def declare_reduction_complex_implicit():
    data = [-1j, 2j, 3j, 1j, 4j, 5j, 6j, -7j]
    res = csum(data)
    return res
