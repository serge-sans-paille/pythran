# cython: np_pythran=True

import numpy as np
cimport numpy as np

def indexing():
    cdef np.ndarray[double, ndim=2] A = np.random.rand(1, 1)
    cdef double a
    with nogil:
        A[0, 0] = 12.
        a = A[0, 0]
    return a

