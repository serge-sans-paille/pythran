#pythran export arc_distance(float [], float[], float[], float[])
#runas import numpy as np; arc_distance(np.array([12.4,0.5,-5.6,12.34,9.21]),np.array([-5.6,3.4,2.3,-23.31,12.6]),np.array([3.45,1.5,55.4,567.0,43.2]),np.array([56.1,3.4,1.34,-56.9,-3.4]))

from __future__ import division
 
cimport cython
import numpy as np
cdef extern from "math.h" nogil:
    double sqrt(double)
    double sin(double)
    double cos(double)
    double atan2(double, double)

@cython.boundscheck(False)
@cython.wraparound(False)
def arc_distance(double [:] theta_1, double [:] phi_1, double [:] theta_2, double [:] phi_2):
    """
    Calculates the pairwise arc distance between all points in vector a and b.
    """
    cdef:
        int i, n
        double temp
        double [:] distance_matrix
    n = theta_1.shape[0]
    distance_matrix = np.zeros((n))
    for i in range(n):
        temp = sin((theta_2[i]-theta_1[i])/2)**2+cos(theta_1[i])*cos(theta_2[i])*sin((phi_2[i]-phi_1[i])/2)**2
        distance_matrix[i] = 2 * (atan2(sqrt(temp),sqrt(1-temp)))
    return distance_matrix
