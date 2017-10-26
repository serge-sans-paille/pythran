import numpy as np
cimport numpy as np
cimport cython

DTYPE = np.double
ctypedef np.double_t DTYPE_t

@cython.boundscheck(False)
def matrix_multiply(np.ndarray[DTYPE_t, ndim=2, negative_indices=False] m0, np.ndarray[DTYPE_t, ndim=2, negative_indices=False] m1):
    cdef np.ndarray[DTYPE_t, ndim=2, negative_indices=False] new_matrix = np.zeros((m0.shape[0],m1.shape[1]))
    cdef int i, j, k
    cdef double r
    "omp parallel for private(i,j,k,r)"
    for i in xrange(m0.shape[0]):
        for j in xrange(m1.shape[1]):
            r=0
            for k in xrange(m1.shape[0]):
                r += m0[i,k]*m1[k,j]
            new_matrix[i,j]=r
    return new_matrix
