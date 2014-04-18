#pythran export arc_distance(float [], float[], float[], float[])
#runas import numpy as np; arc_distance(np.array([12.4,0.5,-5.6,12.34,9.21]),np.array([-5.6,3.4,2.3,-23.31,12.6]),np.array([3.45,1.5,55.4,567.0,43.2]),np.array([56.1,3.4,1.34,-56.9,-3.4]))
#bench import numpy.random; N=5000000; a, b, c, d = numpy.random.rand(N), numpy.random.rand(N), numpy.random.rand(N), numpy.random.rand(N); arc_distance(a, b, c, d)

import numpy as np
def arc_distance(theta_1, phi_1,
                 theta_2, phi_2):
    """
    Calculates the pairwise arc distance between all points in vector a and b.
    """
    temp = np.sin((theta_2-theta_1)/2)**2+np.cos(theta_1)*np.cos(theta_2)*np.sin((phi_2-phi_1)/2)**2
    distance_matrix = 2 * (np.arctan2(np.sqrt(temp),np.sqrt(1-temp)))
    return distance_matrix
