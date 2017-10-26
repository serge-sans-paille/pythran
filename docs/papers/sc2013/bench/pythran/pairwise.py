#from http://jakevdp.github.com/blog/2012/08/24/numba-vs-cython/
#runas import random,numpy ; X = [ [random.random() for i in xrange(10000) ] for j in xrange(100) ] ; X = numpy.array(X) ; pairwise(X)
#pythran export pairwise(float [] [])

import math, numpy
def pairwise(X):
    M = X.shape[0]
    N = X.shape[1]
    D = numpy.zeros((M,N))
    "omp parallel for private(i,j,d,k,tmp)"
    for i in xrange(M):
        for j in xrange(M):
            d = 0.0
            for k in xrange(N):
                tmp = X[i,k] - X[j,k]
                d += tmp * tmp
            D[i,j] = math.sqrt(d)
    return D

