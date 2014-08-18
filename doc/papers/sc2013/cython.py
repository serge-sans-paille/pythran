#!/usr/bin/env python
import numpy as np
import matplotlib.mlab as mlab
import matplotlib.pyplot as plt
import math

with file("cython.dat") as fd:
    r = list()
    for line in fd:
        r.append(filter(None, line.split(' ')))

    x = np.array(
            [
                [float(_[1]) for _ in r],
                [float(_[2]) for _ in r],
                [float(_[3]) for _ in r],
                [float(_[4]) for _ in r],
                ]
            )
    y = np.zeros(x.shape)

    for i,j in enumerate(x):
        y[i] = j/x[2]

    for i in xrange(y.shape[0]):
        for j in xrange(x.shape[1]):
            if math.isinf(y[i][j]):
                y[i][j] = x[i][j]/x[0][j]
            if math.isnan(y[i][j]):
                y[i][j] = 0
        
    fig = plt.figure(1, figsize=(8,4))

    hatches = [ ' ' , 'x', ' ' , 'x' , '+' , 'x' , 'o' , 'O' , '.' , '*' ]
    colors  = [ 'grey' , 'grey', 'w', 'w' ]
    p = [0]*len(x)
    for i,j in enumerate(y):
        p[i] = plt.bar(range(i,y.size+len(y)+len(y)-1, len(y) +1), j, hatch=hatches[i], color=colors[i])

    #plt.xlabel('Comparison between cython and pythran')
    plt.xticks(range(2,y.size+len(y)+1, len(y) +1), [_[0] for _ in r ] )
    plt.ylabel('normalized execution time')
    #plt.title(r'$comparaison between cython and pythran with/without parallelism$')
    plt.grid(True, axis='y')
    plt.legend( (p[0][0], p[1][0], p[2][0], p[3][0]), ('Pythran', 'Pythran + OMP', 'Cython', 'Cython + OMP') , bbox_to_anchor=(0., 1.02, 1., .102), loc=2, ncol=2, mode="expand", borderaxespad=0.)
    plt.savefig('cython.pdf',format='pdf')
