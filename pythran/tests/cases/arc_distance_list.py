#from https://bitbucket.org/FedericoV/numpy-tip-complex-modeling/src/806c968e3705/src/simulations/list_arc_distance.py?at=default
from math import sin, cos, atan2, sqrt, pi
from random import random

#pythran export arc_distance_list( (float, float) list, (float, float) list)
#runas arc_distance_list([(12.4,0.5),(-5.6,12.34),(9.21,-5.6),(3.4,2.3),(-23.31,12.6)],[(3.45,1.5),(55.4,567.0),(43.2,56.1),(3.4,1.34),(-56.9,-3.4)])
#bench import random; N=1000; a = [(random.random(), random.random()) for i in xrange(N)]; b = [(random.random(), random.random()) for i in xrange(N)]; arc_distance_list(a,b)
def arc_distance_list(a, b):
    distance_matrix = []
    for theta_1, phi_1 in a:
        temp_matrix = [ 2 * (atan2(sqrt(temp), sqrt(1 - temp))) for temp in [ sin((theta_2 - theta_1) / 2) ** 2 + cos(theta_1) * cos(theta_2) * sin((phi_2 - phi_1) / 2) ** 2  for theta_2, phi_2 in b ] ]
        distance_matrix.append(temp_matrix)

    return distance_matrix

#print  arc_distance_list([(12.4,0.5),(-5.6,12.34),(9.21,-5.6),(3.4,2.3),(-23.31,12.6)],[(3.45,1.5),(55.4,567.0),(43.2,56.1),(3.4,1.34),(-56.9,-3.4)])
