import numpy as np
def aaa(a):
    grid = np.empty((a, ))
    # omp parallel for private(i, j)
    for i in range(a):
        j = i * i
        grid[i] = j
    return grid

def pythran_forward_substitution():
    from random import randint
    return aaa(randint(5,5))
