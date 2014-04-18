#from http://stackoverflow.com/questions/19277244/fast-weighted-euclidean-distance-between-points-in-arrays/19277334#19277334
#pythran export slow_wdist(float64 [][], float64 [][], float64[][])
#runas import numpy as np ; A = np.arange(6.).reshape((2,3)) ; B =  np.arange(1,7.).reshape((2,3)) ; W = np.arange(2,8.).reshape((2,3)) ; slow_wdist(A,B,W)
#bench S = 520.; import numpy as np ; A = np.arange(S).reshape((2,S / 2)) ; B =  np.arange(1,1 + S).reshape((2,S / 2)) ; W = np.arange(2,S + 2).reshape((2,S / 2)) ; slow_wdist(A,B,W)

import numpy as np
def slow_wdist(A, B, W):

    k,m = A.shape
    _,n = B.shape
    D = np.zeros((m, n))

    for ii in xrange(m):
        for jj in xrange(n):
            wdiff = (A[:,ii] - B[:,jj]) / W[:,ii]
            D[ii,jj] = np.sqrt((wdiff**2).sum())
    return D
