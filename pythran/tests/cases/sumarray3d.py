#from http://stackoverflow.com/questions/20076030/lack-of-speedup-and-erroneous-results-with-openmp-and-cython/20183767#20183767
#pythran export summation(float32[][], float32[], float32[][])
#runas import numpy as np ; N=30 ; pos = np.arange(N*3., dtype=np.float32).reshape((N,3)) ; w = np.ones(N, dtype=np.float32) ; p =  np.arange(N*3., dtype=np.float32).reshape((N,3)) ; summation(pos, w, p)
#bench import numpy as np ; N=300 ; pos = np.arange(1, N*3. + 1, dtype=np.float32).reshape((N,3)) ; w = np.ones(N, dtype=np.float32) ; p =  np.arange(N*3., dtype=np.float32).reshape((N,3)) ; summation(pos, w, p)
import numpy as np
def summation(pos, weights, points):
  n_points = len(points)
  n_weights = len(weights)
  sum_array3d = np.zeros((n_points,3))
  def compute(i):
    pxi = points[i, 0]
    pyi = points[i, 1]
    pzi = points[i, 2]
    total = 0.0
    for j in xrange(n_weights):
      weight_j = weights[j]
      xj = pos[j,0]
      yj = pos[j,1]
      zj = pos[j,2]
      dx = pxi - pos[j, 0]
      dy = pyi - pos[j, 1]
      dz = pzi - pos[j, 2]
      dr = 1.0/np.sqrt(dx*dx + dy*dy + dz*dz)
      total += weight_j * dr
      sum_array3d[i,0] += weight_j * dx
      sum_array3d[i,1] += weight_j * dy
      sum_array3d[i,2] += weight_j * dz
    return total 
  sum_array = np.array([compute(i) for i in xrange(n_points)])
  return sum_array, sum_array3d
