#pythran export pi_estimate(int,float list, int)
#runas pi_estimate(4000,[x/100. for x in range(100)],100)
#bench pi_estimate(2200000,[x/1000. for x in range(1000)],1000)
from math import sqrt, pow
from random import random

def pi_estimate(DARTS,rand,randsize):
    hits = 0
    "omp parallel for reduction(+:hits)"
    for i in xrange (0, DARTS):
        x = rand[i%randsize]
        y = rand[(randsize-i)%randsize]
        dist = sqrt(pow(x, 2) + pow(y, 2))
        if dist <= 1.0:
            hits += 1.0
    # hits / throws = 1/4 Pi
    pi = 4 * (hits / DARTS)
    return pi

