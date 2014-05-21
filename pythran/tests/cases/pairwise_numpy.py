#from http://jakevdp.github.com/blog/2012/08/24/numba-vs-cython/
#runas import numpy as np ; X = np.linspace(0,10,20000).reshape(200,100) ; pairwise(X)
#bench import numpy as np ; X = np.linspace(0,10,10000).reshape(100,100) ; pairwise(X)
#pythran export pairwise(float [][])

import numpy as np
def pairwise(X):
    M, N = X.shape
    D = np.empty((M,M))
    for i in range(M):
        for j in range(M):
            d = 0.0
            for k in xrange(N):
                tmp = X[i,k] - X[j,k]
                d += tmp * tmp
            D[i,j] = np.sqrt(d)
    return D
