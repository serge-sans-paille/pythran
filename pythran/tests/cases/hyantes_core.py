#pythran export run(float, float, float, float, float, float, int, int, float list list)
import math
def run(xmin, ymin, xmax, ymax, step, range_, range_x, range_y, t):
    pt = [ [ [  (xmin+step*i)*180/math.pi, (ymin+step*j)*180/math.pi, 0.] for j in xrange(range_y) ] for i in xrange(range_x)]
    for i in xrange(range_x):
        for j in xrange(range_y):
            for k in t:
                tmp = 6368.* math.acos( math.cos(xmin+step*i)*math.cos( k[0] ) * math.cos((ymin+step*j)-k[1])+  math.sin(xmin+step*i)*math.sin(k[0]))
                if tmp < range_:
                    pt[i][j][2]+= k[2] / (1+tmp)
    return pt
