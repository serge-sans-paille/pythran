#from:  https://stackoverflow.com/questions/50658884/why-this-numba-code-is-6x-slower-than-numpy-code
#runas import numpy as np; x1 = np.array([[1.,2,3]]) ; x2 = np.array([[1.,2,3],[2,3,4], [3,4,5], [4,5,6], [5,6,7]]); euclidean_distance_square(x1, x2)
#pythran export euclidean_distance_square(float64[1,:], float64[:,:])
import numpy as np
def euclidean_distance_square(x1, x2):
    return -2*np.dot(x1, x2.T) + np.sum(np.square(x1), axis=1)[:, np.newaxis] + np.sum(np.square(x2), axis=1)
