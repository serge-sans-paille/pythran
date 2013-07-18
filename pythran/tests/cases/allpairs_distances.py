#pythran export allpairs_distances()
#runas allpairs_distances()
import numpy as np

def dists(X,Y):
  return np.array([[np.sum( (x-y) ** 2) for x in X] for y in Y])

def allpairs_distances():
    d = 100
    #X = np.random.randn(1000,d)
    #Y = np.random.randn(200,d)
    X = np.ones((1000,d))
    Y = np.ones((200,d))
    return dists(X,Y)
