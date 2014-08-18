import hyantes_core
from numpy import array, savetxt, zeros
from math import pi
import operator
import sys

def run():
    with file('Rhone-alpesXYLongLat_pop.txt') as data_in:
        towns = []
        for line in data_in:
            lat, lon, val = [x for x in line.split('\t') if x]
            towns.append((float(lat)*pi/180, float(lon)*pi/180, float(val)))
        towns = array(towns)
    grid = hyantes_core.run(1.1*pi/180., 32*pi/180, 4*pi/180, 35*pi/180, 0.01*pi/180, 40, 290, 299, towns)
    with file('out', 'w') as data_out:
        for i in xrange(290):
            for j in xrange(299):
                data_out.write("{0} {1} {2}\n".format( grid[i,j,0], grid[i,j,1], grid[i,j,2]) )
            data_out.write('\n')
    #gnuplot -persist -e "set pm3d map; set size ratio 1; splot 'out'
if __name__ == '__main__':
    run()
