#pythran export run(float, float, float, float, float, float, int, int, float [][])
import numpy
import math
def run(xmin, ymin, xmax, ymax, step, range_, range_x, range_y, t):
    pt = numpy.zeros((range_x, range_y, 3))
    for i in xrange(range_x):
        for j in xrange(range_y):
            pt[i,j,0], pt[i,j,1] = (xmin+step*i)*180/math.pi, (ymin+step*j)*180/math.pi
            for k in t:
                tmp = 6368.* math.acos( math.cos(xmin+step*i)*math.cos( k[0] ) * math.cos((ymin+step*j)-k[1])+  math.sin(xmin+step*i)*math.sin(k[0]))
                if tmp < range_:
                    pt[i,j,2]+= k[2] / (1+tmp)
    return pt
