# taken from http://oddbloke.uwcs.co.uk/parallel_benchmarks/
#pythran export sum_primes(int)
import math
def isprime(n):
    """Returns True if n is prime and False otherwise"""
    if n < 2:
        return False
    if n == 2:
        return True
    max = int(math.ceil(math.sqrt(n)))
    i = 2
    while i <= max:
        if n % i == 0:
            return False
        i += 1
    return True

def sum_primes(n):
    """Calculates sum of all primes below given integer n"""
    return sum([x for x in xrange(2,n) if isprime(x)])
