#from https://gist.github.com/mblondel/c99e575a5207c76a99d714e8c6e08e89
#pythran export projection_simplex(float[], int)
#runas import numpy as np; np.random.seed(0); x = np.random.rand(10); projection_simplex(x, 1)

import numpy as np
def projection_simplex(v, z=1):
    """
    Old implementation for test and benchmark purposes.
    The arguments v and z should be a vector and a scalar, respectively.
    """
    n_features = v.shape[0]
    u = np.sort(v)[::-1]
    cssv = np.cumsum(u) - z
    ind = np.arange(n_features) + 1
    cond = u - cssv / ind > 0
    rho = ind[cond][-1]
    theta = cssv[cond][-1] / float(rho)
    w = np.maximum(v - theta, 0)
    return w
