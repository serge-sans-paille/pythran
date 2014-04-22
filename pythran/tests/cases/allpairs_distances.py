#pythran export allpairs_distances(int)
#runas allpairs_distances(100)
#bench allpairs_distances(100)
import numpy as np

def dists(X,Y):
  return np.array([[np.sum( (x-y) ** 2) for x in X] for y in Y])

def allpairs_distances(d):
    #X = np.random.randn(1000,d)
    #Y = np.random.randn(200,d)
    X = np.arange(600*d).reshape((600,d))
    Y = np.arange(200*d).reshape((200,d))
    return dists(X,Y)
