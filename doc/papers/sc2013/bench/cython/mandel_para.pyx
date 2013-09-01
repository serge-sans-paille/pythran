cimport cython
cimport numpy as np
import numpy as np
from cython.parallel import parallel, prange

DTYPE = np.double
ctypedef np.double_t DTYPE_t

@cython.boundscheck(False)
@cython.cdivision(True)
def mandel(int size, int x_center, int y_center, int max_iteration):
    cdef int i, j, iteration, color_value
    cdef double x, y, a, b
    cdef np.ndarray[DTYPE_t, ndim=2, negative_indices=False] out = np.zeros((size,size))
    with nogil, parallel():
        for i in prange(size):#, schedule="static", chunksize=5):
            for j in xrange(size):
                x = x_center + 4.0*float(i-size/2)/size
                y = y_center + 4.0*float(j-size/2)/size

                a = 0.0
                b = 0.0
                iteration = 0

                while (a**2 + b**2 <= 4.0 and iteration < max_iteration):
                    a= a**2 - b**2 + x
                    b= 2*a*b + y
                    iteration = iteration + 1
                if iteration == max_iteration:
                    color_value = 255
                else:
                    color_value = iteration*10 % 255
                out[i,j]=color_value
    return out
