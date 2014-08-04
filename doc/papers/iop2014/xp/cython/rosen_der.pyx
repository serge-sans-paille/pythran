# Authors: Serge Guelton
# License: MIT

import numpy as np
cimport cython

@cython.boundscheck(False)
@cython.wraparound(False)
def rosen_der(double[:] x):
    cdef int n = x.shape[0]
    cdef int i
    cdef double[:] der = np.zeros_like(x)

    der[0] = -400*x[0]*(x[1]-x[0]**2) - 2*(1-x[0])
    for i in range(1,n-1):
        der[i] = (200*(x[i] - x[i - 1]**2)
                  - 400 * (x[i + 1] - x[i]**2)*x[i]
                  - 2 * (1 - x[i]))
    der[n - 1] = 200 * (x[-1] - x[-2]**2)
    return der


