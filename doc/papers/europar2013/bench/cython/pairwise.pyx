#from http://jakevdp.github.com/blog/2012/08/24/numba-vs-cython/
#runas import random,numpy ; X = [ [random.random() for i in xrange(10000) ] for j in xrange(30) ] ; X = numpy.array(X) ; pairwise(X)
#pythran export pairwise(double [] [])

from libc.math cimport sqrt
import numpy as np
cimport numpy as np
cimport cython

DTYPE = np.double
ctypedef np.double_t DTYPE_t

@cython.boundscheck(False)
def pairwise(np.ndarray[DTYPE_t, ndim=2, negative_indices=False] X):
    cdef long i,j,k, M, N
    cdef double d, tmp
    M = X.shape[0]
    N = X.shape[1]
    cdef np.ndarray[DTYPE_t, ndim=2, negative_indices=False] D = np.zeros((M,N))
    for i in xrange(M):
        for j in xrange(M):
            d = 0.0
            for k in xrange(N):
                tmp = X[i,k] - X[j,k]
                d += tmp * tmp
            D[i,j] = sqrt(d)
    return D

