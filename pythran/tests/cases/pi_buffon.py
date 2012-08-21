#runas pi_estimate(10000000)
#pythran export pi_estimate(int)
from math import sqrt, pow
from random import random

def pi_estimate(DARTS):
    hits = 0
    throws = 0
    for i in range (1, DARTS):
    	throws += 1
    	x = random()
    	y = random()
    	dist = sqrt(pow(x, 2) + pow(y, 2))
    	if dist <= 1.0:
    		hits = hits + 1.0
    
    # hits / throws = 1/4 Pi
    pi = 4 * (hits / throws)
    return pi

