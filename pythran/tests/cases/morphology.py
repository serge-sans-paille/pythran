#skip.pythran export dilate_decompose(int[][], int)
#pythran export dilate_decompose_loops(float[][], int)
#skip.pythran export dilate_decompose_interior(int[][], int[][])
#skip.runas import numpy as np ; image = np.random.randint(0, 256,  (width, height)) / 256.0 ; dilate_decompose_loops(image)
#runas import numpy as np ; image = np.tri(100, 200) /2.0 ; dilate_decompose_loops(image, 4)
#bench import numpy as np ; image = np.tri(500, 600) /2.0 ; dilate_decompose_loops(image, 4)

from numpy import empty_like

def dilate_decompose_loops(x, k):
  m,n = x.shape
  y = empty_like(x)
  for i in xrange(m):
    for j in xrange(n):
      left_idx = max(0, i-k/2)
      right_idx = min(m, i+k/2+1)
      currmax = x[left_idx, j]
      for ii in xrange(left_idx+1, right_idx):
        elt = x[ii, j]
        if elt > currmax:
          currmax = elt
      y[i, j] = currmax
  z = empty_like(x)
  for i in xrange(m):
    for j in xrange(n):
      left_idx = max(0, j-k/2)
      right_idx = min(n, j+k/2+1)
      currmax = y[i,left_idx]
      for jj in xrange(left_idx+1, right_idx):
        elt = y[i,jj]
        if elt > currmax:
          currmax = elt
      z[i,j] = currmax
  return z

#def dilate_1d_naive(x_strip,  k):
#  """
#  Given a 1-dimensional input and 1-dimensional output, 
#  fill output with 1d dilation of input 
#  """
#  nelts = len(x_strip)
#  y_strip = empty_like(x_strip)
#  half = k / 2 
#  for idx in xrange(nelts):
#    left_idx = max(idx-half,0)
#    right_idx = min(idx+half+1, nelts)
#    currmax = x_strip[left_idx]
#    for j in xrange(left_idx+1, right_idx):
#      elt = x_strip[j]
#      if elt > currmax:
#        currmax = elt
#    y_strip[idx] = currmax 
#  return y_strip
#
#def dilate_decompose(x, k): 
#  import numpy as np
#  m,n = x.shape
#  y = np.array([dilate_1d_naive(x[row_idx, :], k) for row_idx in xrange(m)])
#  return np.array([dilate_1d_naive(y[:, col_idx], k) for col_idx in xrange(n)]).T
#
#def dilate_1d_interior(x_strip, k):
#  
#  nelts = len(x_strip)
#  y_strip = empty_like(x_strip)
#  half = k / 2 
#  
#  interior_start = half+1
#  interior_stop = max(nelts-half, interior_start)
#  
#  # left boundary
#  for i in xrange(min(half+1, nelts)):
#    left_idx = max(i-half,0)
#    right_idx = min(i+half+1, nelts)
#    currmax = x_strip[left_idx]
#    for j in xrange(left_idx+1, right_idx):
#      elt = x_strip[j]
#      if elt > currmax:
#        currmax = elt
#    y_strip[i] = currmax 
#    
#  #interior 
#  for i in xrange(interior_start, interior_stop):
#    left_idx = i-half
#    right_idx = i+half+1
#    currmax = x_strip[left_idx]
#    for j in xrange(left_idx+1, right_idx):
#      elt = x_strip[j]
#      if elt > currmax:
#        currmax = elt
#    y_strip[i] = currmax 
#  
#  # right boundary
#  for i in xrange(interior_stop, nelts):
#    left_idx = max(i-half, 0)
#    right_idx = nelts
#    currmax = x_strip[left_idx]
#    for j in xrange(left_idx+1, right_idx):
#      elt = x_strip[j]
#      if elt > currmax:
#        currmax = elt
#    y_strip[i] = currmax 
#  return y_strip 
#
#def dilate_decompose_interior(x, k): 
#  m,n = x.shape
#  y = np.array([dilate_1d_interior(x[row_idx, :],k) for row_idx in xrange(m)])
#  return np.array([dilate_1d_interior(y[:, col_idx],k) for col_idx in xrange(n)]).T
