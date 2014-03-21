#runas solve(2000000)
#pythran export solve(int)
def solve(max):
    '''
    The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.
    
    Find the sum of all the primes below two million.
    '''

    sieve = [True] * max    # Sieve is faster for 2M primes

    def mark(sieve, x):
        for i in xrange(x+x, len(sieve), x):
            sieve[i] = False

    for x in xrange(2, int(len(sieve) ** 0.5) + 1):
        if sieve[x]: mark(sieve, x)

    return sum(i for i in xrange(2, len(sieve)) if sieve[i])
