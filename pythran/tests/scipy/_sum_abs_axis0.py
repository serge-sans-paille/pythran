import numpy as np

#pythran export _sum_abs_axis0(float[:,:])
def _sum_abs_axis0(X):
    block_size = 2**20
    r = None
    for j in range(0, X.shape[0], block_size):
        y = np.sum(np.abs(X[j:j+block_size]), axis=0)
        if r is None:
            r = y
        else:
            r += y
    return r
