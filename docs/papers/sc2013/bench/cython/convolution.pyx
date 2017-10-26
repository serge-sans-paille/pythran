import numpy as np
cimport numpy as np
cimport cython

DTYPE = np.double
ctypedef np.double_t DTYPE_t

@cython.boundscheck(False)
def convolution(np.ndarray[DTYPE_t, ndim=2, negative_indices=False] A):
    cdef int m = A.shape[0]
    cdef int n = A.shape[1]
    cdef np.ndarray[DTYPE_t, ndim=2, negative_indices=False] B = np.zeros((m,n))

    cdef double c11 = 2.0
    cdef double c21 = 5.0
    cdef double c31 = -8.0
    cdef double c12 = -3.0
    cdef double c22 = 6.0
    cdef double c32 = -9.0
    cdef double c13 = 4.0
    cdef double c23 = 7.0
    cdef double c33 = 10.0
    cdef int i,j
    for i in xrange(1, m - 1):
        for j in xrange(1, n - 1):
          B[i,j] = c11 * A[i - 1,j - 1] + c12 * A[i + 0,j - 1] + c13 * A[i + 1,j - 1]\
          + c21 * A[i - 1,j + 0] + c22 * A[i + 0,j + 0] + c23 * A[i + 1,j + 0]\
          + c31 * A[i - 1,j + 1] + c32 * A[i + 0,j + 1] + c33 * A[i + 1,j + 1]
    return B 
