#runas solve(1000000)
#pythran export solve(int)
def solve(a):
    '''
    The number, 197, is called a circular prime because all rotations of the digits: 197, 971, and 719, are themselves prime.
    
    There are thirteen such primes below 100: 2, 3, 5, 7, 11, 13, 17, 31, 37, 71, 73, 79, and 97.
    
    How many circular primes are there below one million?
    '''

    sieve = [True] * a
    sieve[0] = sieve[1] = False

    def mark(sieve, x):
        for i in xrange(x+x, len(sieve), x):
            sieve[i] = False

    for x in xrange(2, int(len(sieve) ** 0.5) + 1):
        mark(sieve, x)

    def circular(n):
        digits = []
        while n > 0:
            digits.insert(0, str(n % 10))
            n = n / 10
        for d in xrange(1, len(digits)):
            yield int(''.join(digits[d:] + digits[0:d]))

    count = 0
    for n, p in enumerate(sieve):
        if p:
            iscircularprime = 1
            for m in circular(n):
                if not sieve[m]:
                    iscircularprime = 0
                    break
            if iscircularprime:
                count = count + 1

    return count
