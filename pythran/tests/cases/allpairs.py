import numpy as np
#pythran export sqr_dists(float[][], float[][])
#pythran export sqr_dists_loops(float[][], float[][])

def sqr_dists(X,Y):
  return np.array([[np.sum( (x-y) ** 2) for x in X] for y in Y])

def sqr_dists_loops(X,Y):
  m,n = X.shape[0], Y.shape[0]
  D = np.zeros((m,n))
  for i in xrange(m):
    for j in xrange(n):
      D[i,j] = np.sum( (X[i] -Y[j]) ** 2)
  return D

