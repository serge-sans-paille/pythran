#from http://rosettacode.org/wiki/Average_loop_length#Python
#pythran export analytical(int)
#pythran export testing(int, int)
#runas analytical(10)
#runas avg = testing(10, 10**5); theory = analytical(10); abs((avg / theory - 1) * 100) < 0.1

#from __future__ import division # Only necessary for Python 2.X
from math import factorial
from random import randrange

def analytical(n):
	return sum(factorial(n) / pow(n, i) / float(factorial(n -i)) for i in range(1, n+1))

def testing(n, times):
    count = 0
    for i in range(times):
        x, bits = 1, 0
        while not (bits & x):
            count += 1
            bits |= x
            x = 1 << randrange(n)
    return count / times
