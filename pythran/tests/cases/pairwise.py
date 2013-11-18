#from http://jakevdp.github.com/blog/2012/08/24/numba-vs-cython/
#runas X = [ [i/100.+j for i in xrange(100) ] for j in xrange(30) ] ; pairwise(X)
#pythran export pairwise(float list list)

import math
def pairwise(X):
    M = len(X)
    N = len(X[0])
    D = [ [0 for x in xrange(M) ] for y in xrange(M) ]
    "omp parallel for"
    for i in xrange(M):
        for j in xrange(M):
            d = 0.0
            for k in xrange(N):
                tmp = X[i][k] - X[j][k]
                d += tmp * tmp
                D[i][j] = math.sqrt(d)
    return D
