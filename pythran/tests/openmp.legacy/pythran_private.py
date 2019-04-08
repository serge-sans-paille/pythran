
import numpy as np
def aaa(a):
    grid = np.empty((a, ))
    # omp parallel for private(i, j)
    for i in range(a):
        if i % 2:
            j = i * i
        else:
            j = i * i *3
        grid[i] = j

def pythran_private():
    from random import randint
    return aaa(randint(5,5))
