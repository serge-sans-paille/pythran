#
# Copyright (C)  Tyler Reddy, Richard Gowers, and Max Linke, 2016
#
# Distributed under the same BSD license as Scipy.
#
# adapted from scipy's cython version
import numpy as np
import numpy.random as random

#pythran export directed_hausdorff(float64[:,:], float64[:,:], int)
#pythran export directed_hausdorff_noshuffle(float64[:,:], float64[:,:])
#runas import numpy as np; x = np.arange((100 * 100.)).reshape(100,-1); y =  np.ones((100,100)) * 3; directed_hausdorff_noshuffle(x, y)

def directed_hausdorff(ar1, ar2, seed=0):

    N1, data_dims = ar1.shape
    N2 = ar2.shape[0]
    i_store = j_store = i_ret = j_ret = 0

    # shuffling the points in each array generally increases the likelihood of
    # an advantageous break in the inner search loop and never decreases the
    # performance of the algorithm
    random.seed(seed)
    resort1 = np.arange(N1)
    resort2 = np.arange(N2)
    random.shuffle(resort1)
    random.shuffle(resort2)
    ar1 = np.asarray(ar1)[resort1]
    ar2 = np.asarray(ar2)[resort2]

    cmax = 0
    for i in range(N1):
        cmin = np.inf
        for j in range(N2):
            d = np.sum((ar1[i] - ar2[j]) ** 2)
            # faster performance with square of distance
            # avoid sqrt until very end
            if d < cmax: # break out of `for j` loop
                break

            if d < cmin: # always true on first iteration of for-j loop
                cmin = d
                i_store = i
                j_store = j
        else:

            # always true on first iteration of for-j loop, after that only
            # if d >= cmax
            if cmin != np.inf and cmin > cmax:
                cmax = cmin
                i_ret = i_store
                j_ret = j_store

    return np.sqrt(cmax), resort1[i_ret], resort2[j_ret]

def directed_hausdorff_noshuffle(ar1, ar2, seed=0):

    N1, data_dims = ar1.shape
    N2 = ar2.shape[0]
    i_store = j_store = i_ret = j_ret = 0

    resort1 = np.arange(N1)
    resort2 = np.arange(N2)
    ar1 = np.asarray(ar1)[resort1]
    ar2 = np.asarray(ar2)[resort2]

    cmax = 0
    for i in range(N1):
        cmin = np.inf
        for j in range(N2):
            d = np.sum((ar1[i] - ar2[j]) ** 2)
            # faster performance with square of distance
            # avoid sqrt until very end
            if d < cmax: # break out of `for j` loop
                break

            if d < cmin: # always true on first iteration of for-j loop
                cmin = d
                i_store = i
                j_store = j
        else:

            # always true on first iteration of for-j loop, after that only
            # if d >= cmax
            if cmin != np.inf and cmin > cmax:
                cmax = cmin
                i_ret = i_store
                j_ret = j_store

    return np.sqrt(cmax), resort1[i_ret], resort2[j_ret]

