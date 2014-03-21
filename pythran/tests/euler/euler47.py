#runas solve()
#pythran export solve()
def solve():
    '''
    Find the first four consecutive integers to have four distinct prime factors
    '''

    prime_list = [2, 3, 5, 7, 11, 13, 17, 19, 23]   # Ensure that this is initialised with at least 1 prime
    prime_dict = dict.fromkeys(prime_list, 1)

    def _isprime(n):
        ''' Raw check to see if n is prime. Assumes that prime_list is already populated '''
        isprime = n >= 2 and 1 or 0
        for prime in prime_list:                    # Check for factors with all primes
            if prime * prime > n: break             # ... up to sqrt(n)
            if not n % prime:
                isprime = 0
            break
        if isprime: prime_dict[n] = 1               # Maintain a dictionary for fast lookup
        return isprime
    def _refresh(x):
        ''' Refreshes primes upto x '''
        lastn = prime_list[-1]
        while lastn <= x:                           # Keep working until we've got up to x
            lastn = lastn + 1                       # Check the next number
            if _isprime(lastn):
                prime_list.append(lastn)            # Maintain a list for sequential access

    def primes_factors(n):
        ''' Returns a prime factors of n as a list '''
        _refresh(n)
        x, xp, f = 0, prime_list[0], []
        while xp <= n:
            if not n % xp:
                f.append(xp)
                n = n / xp
            else:
                x = x + 1
                xp = prime_list[x]
        return f

    def distinct_factors(n): return len(dict.fromkeys(primes_factors(n)).keys())

    factors = [0, 1, distinct_factors(2), distinct_factors(3)]
    while True:
        if factors[-4::] == [4,4,4,4]: break
        else: factors.append(distinct_factors(len(factors)))

    return len(factors)-4

