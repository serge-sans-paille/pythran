import numpy as np
cimport numpy as np
cimport cython
from cython.parallel import parallel, prange

DTYPE = np.float
ctypedef np.float_t DTYPE_t

@cython.boundscheck(False)
def convolution(np.ndarray[DTYPE_t, ndim=2, negative_indices=False] A):
    cdef int m = A.shape[0]
    cdef int n = A.shape[1]
    cdef np.ndarray[DTYPE_t, ndim=2, negative_indices=False] B = np.zeros((m,n))

    cdef float c11 = 2.0
    cdef float c21 = 5.0
    cdef float c31 = -8.0
    cdef float c12 = -3.0
    cdef float c22 = 6.0
    cdef float c32 = -9.0
    cdef float c13 = 4.0
    cdef float c23 = 7.0
    cdef float c33 = 10.0
    cdef int i,j
    with nogil, parallel():
        for i in prange(1, m - 1):
            for j in xrange(1, n - 1):
              B[i,j] = c11 * A[i - 1,j - 1] + c12 * A[i + 0,j - 1] + c13 * A[i + 1,j - 1]\
              + c21 * A[i - 1,j + 0] + c22 * A[i + 0,j + 0] + c23 * A[i + 1,j + 0]\
              + c31 * A[i - 1,j + 1] + c32 * A[i + 0,j + 1] + c33 * A[i + 1,j + 1]
    return B 
