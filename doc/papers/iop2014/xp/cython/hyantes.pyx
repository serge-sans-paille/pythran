#pythran export run(float, float, float, float, float, float, int, int, float[][])
#runas import numpy ; run(0,0,90,90, 1, 100, 80, 80, numpy.array([ [i/10., i/10., i/20.] for i in xrange(80)],dtype=numpy.double))
import numpy as np
cimport cython
@cython.boundscheck(False)
@cython.wraparound(False)
def run(double xmin, double ymin, double xmax, double ymax, double step, double range_, int range_x, int range_y, double [:,:] t):
    cdef:
        int X, Y, i, j
        double [:,:] pt
        double tmp
    X,Y = t.shape[0], t.shape[1]
    pt = np.zeros((X,Y))
    for i in range(X):
        for j in range(Y):
            for k in t:
                tmp = 6368.* np.arccos( np.cos(xmin+step*i)*np.cos( k[0] ) * np.cos((ymin+step*j)-k[1])+  np.sin(xmin+step*i)*np.sin(k[0]))
                if tmp < range_:
                    pt[i][j]+=k[2] / (1+tmp)
    return pt
