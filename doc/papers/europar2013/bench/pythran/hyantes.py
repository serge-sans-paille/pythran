#pythran export run(float, float, float, float, float, float, int, int, float [] [])
#runas import numpy as np ; x = [ [i/10., i/10., i/20.] for i in xrange(400) ] ; x = np.array(x) ; run(0,0,90,90, 1, 0.0001, 400, 400, x)
import math, numpy
def run(xmin, ymin, xmax, ymax, step, range_, range_x, range_y, t):
    pt = numpy.zeros((range_x, range_y))
    "omp parallel for private(j,k,tmp)"
    for i in xrange(range_x):
        for j in xrange(range_y):
            for k in xrange(t.shape[0]):
                tmp = 6368.* math.acos( math.cos(xmin+step*i)*math.cos( t[k,0] ) * math.cos((ymin+step*j)-t[k,1])+  math.sin(xmin+step*i)*math.sin(t[k,0]))
                if tmp < range_:
                    pt[i,j]+=t[k,2] / (1+tmp)
    return pt
