#skip.runas pi_estimate(40000000)
#pythran export pi_estimate(int)
from math import sqrt, pow
from random import random

def pi_estimate(DARTS):
    hits = 0
    "omp parallel for private(i,x,y,dist), reduction(+:hits)"
    for i in xrange (0, DARTS):
    	x = random()
    	y = random()
    	dist = sqrt(pow(x, 2) + pow(y, 2))
    	if dist <= 1.0:
            hits += 1.0
    # hits / throws = 1/4 Pi
    pi = 4 * (hits / DARTS)
    return pi

