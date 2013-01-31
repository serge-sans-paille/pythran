#pythran export run(float, float, float, float, float, float, int, int, float list list)
#runas: run(0,0,90,90, 1, 0.0001, 800, 800, [ [i/10., i/10., i/20.] for i in xrange(800) ])
import math
def run(xmin, ymin, xmax, ymax, step, range_, range_x, range_y, t):
    pt = []
    "omp parallel for private(i,j,k,tmp,s,l) ordered"
    for i in xrange(range_x):
        l = []
        for j in xrange(range_y):
            s = 0
            for k in t:
                tmp = 6368.* math.acos( math.cos(xmin+step*i)*math.cos( k[0] ) * math.cos((ymin+step*j)-k[1])+  math.sin(xmin+step*i)*math.sin(k[0]))
                if tmp < range_:
                    s+=k[2] / (1+tmp)
            l.append(s)
        "omp critical"
        pt.append(l)
    return pt
