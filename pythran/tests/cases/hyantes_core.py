#pythran export run(float, float, float, float, float, float, int, int, float list list)
from math import cos, acos, sin, pi
def run(xmin, ymin, xmax, ymax, step, range_, range_x, range_y, t):
    pt = [ [ [  (xmin+step*i)*180/pi, (ymin+step*j)*180/pi, 0.] for j in xrange(range_y) ] for i in xrange(range_x)]
    for i in xrange(range_x):
        for j in xrange(range_y):
            for k in t:
                tmp = 6368.* acos( cos(xmin+step*i)*cos( k[0] ) * cos((ymin+step*j)-k[1])+  sin(xmin+step*i)*sin(k[0]))
                if tmp < range_:
                    pt[i][j][2]+= k[2] / (1+tmp)
    return pt
