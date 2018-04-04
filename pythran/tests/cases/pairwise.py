#from http://jakevdp.github.com/blog/2012/08/24/numba-vs-cython/
#runas X = [ [i/100.+j for i in range(100) ] for j in range(30) ] ; pairwise(X)
#bench X = [ [i/100.+j for i in range(800) ] for j in range(100) ] ; pairwise(X)
#pythran export pairwise(float list list)

import math
def pairwise(X):
    M = len(X)
    N = len(X[0])
    D = [ [0 for x in range(M) ] for y in range(M) ]
    "omp parallel for"
    for i in range(M):
        for j in range(M):
            d = 0.0
            for k in range(N):
                tmp = X[i][k] - X[j][k]
                d += tmp * tmp
            D[i][j] = math.sqrt(d)
    return D
