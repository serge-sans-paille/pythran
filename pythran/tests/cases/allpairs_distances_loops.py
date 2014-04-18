#pythran export allpairs_distances_loops(int)
#runas allpairs_distances_loops(100)
#bench allpairs_distances_loops(100)
import numpy as np

def dists(X,Y):
  result = np.zeros( (X.shape[0], Y.shape[0]), X.dtype)
  for i in xrange(X.shape[0]):
    for j in xrange(Y.shape[0]):
      result[i,j] = np.sum( (X[i,:] - Y[j,:]) ** 2)
  return result

def allpairs_distances_loops(d):
    #X = np.random.randn(1000,d)
    #Y = np.random.randn(200,d)
    X = np.ones((500,d))
    Y = np.ones((200,d))
    return dists(X,Y)
