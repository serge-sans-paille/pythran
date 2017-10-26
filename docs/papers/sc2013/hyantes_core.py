#pythran export run(float, float, float, float, float, float, int, int, float [][])
import math
from numpy import zeros
def run(xmin, ymin, xmax, ymax, step, range_, range_x, range_y, t):
    pt = zeros((range_x, range_y, 3))
    "omp parallel for private(i,j,k,tmp)"
    for i in xrange(range_x):
        for j in xrange(range_y):
            pt[i,j,0], pt[i,j,1] = (xmin+step*i)*180/math.pi, (ymin+step*j)*180/math.pi
            for k in xrange(t.shape[0]):
                tmp = 6368.* math.acos( math.cos(xmin+step*i)*math.cos( t[k,0] ) * math.cos((ymin+step*j)-t[k,1])+  math.sin(xmin+step*i)*math.sin(t[k,0]))
                if tmp < range_:
                    pt[i,j,2]+= t[k,2] / (1+tmp)
    return pt
