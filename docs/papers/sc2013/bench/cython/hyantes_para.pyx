#pythran export run(double, double, double, double, double, double, int, int, double [] [])
#runas import numpy as np ; x = [ [i/10., i/10., i/20.] for i in xrange(400) ] ; x = np.array(x) ; run(0,0,90,90, 1, 0.0001, 400, 400, x)
cimport libc.math as math
import numpy as np
cimport numpy as np
cimport cython
from cython.parallel import parallel, prange

DTYPE = np.double
ctypedef np.double_t DTYPE_t

@cython.boundscheck(False)
@cython.cdivision(True)
def run(double xmin, double ymin, double xmax, double ymax, double step, double range_, int range_x, int range_y, np.ndarray[DTYPE_t, ndim=2, negative_indices=False] t):
    cdef np.ndarray[DTYPE_t, ndim=2, negative_indices=False] pt = np.zeros((range_x, range_y))
    cdef int i,j,k
    cdef double tmp, xi, yj
    "omp parallel for private(j,k,tmp)"
    with nogil, parallel():
        for i in prange(range_x):
            for j in xrange(range_y):
                xi = xmin+step*i
                yj = ymin+step*j
                for k in xrange(t.shape[0]):
                    tmp = 6368.* math.acos( math.cos(xi)*math.cos( t[k,0] ) * math.cos(yj-t[k,1])+  math.sin(xi)*math.sin(t[k,0]))
                    if tmp < range_:
                        pt[i,j]+=t[k,2] / (1+tmp)
    return pt
