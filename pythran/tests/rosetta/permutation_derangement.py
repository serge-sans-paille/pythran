#from http://rosettacode.org/wiki/Permutations/Derangements#Python
from itertools import permutations
import math

#pythran export test(int, int, int)
#runas test(4, 10, 20)

def derangements(n):
    'All deranged permutations of the integers 0..n-1 inclusive'
    return ( perm for perm in permutations(range(n))
             if all(indx != p for indx, p in enumerate(perm)) )

def subfact(n):
    if n == 2 or n == 0:
        return 1
    elif n == 1:
        return 0
    elif  1 <= n <=18:
        return round(math.factorial(n) / math.e)
    elif n.imag == 0 and n.real == int(n.real) and n > 0:
        return (n-1) * ( subfact(n - 1) + subfact(n - 2) )
    else:
        raise ValueError()

def _iterlen(iter):
    'length of an iterator without taking much memory'
    l = 0
    for x in iter:
        l += 1
    return l

def test(n1, n2, n3):
    print("Derangements of %s" % range(n1))
    for d in derangements(n1):
        print("  %s" % (d,))
    print("\nTable of n vs counted vs calculated derangements")
    for n in range(n2):
        print("%2i %-5i %-5i" %
              (n, _iterlen(derangements(n)), subfact(n)))
    print("\n!%i = %i" % (n3, subfact(n3)))
