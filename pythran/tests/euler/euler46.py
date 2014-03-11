#runas solve()
#pythran export solve()
def solve():
    '''
    It was proposed by Christian Goldbach that every odd composite number can be written as the sum of a prime and twice a square.
    
     9 =  7 + 2 x 1^2
    15 =  7 + 2 x 2^2
    21 =  3 + 2 x 3^2
    25 =  7 + 2 x 3^2
    27 = 19 + 2 x 2^2
    33 = 31 + 2 x 1^2
    It turns out that the conjecture was false.
    
    What is the smallest odd composite that cannot be written as the sum of a prime and twice a square?
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

    def prime(x):
        ''' Returns the xth prime '''

        lastn = prime_list[-1]
        while len(prime_list) <= x:                 # Keep working until we've got the xth prime
            lastn = lastn + 1                       # Check the next number
            if _isprime(lastn):
                prime_list.append(lastn)            # Maintain a list for sequential access
        return prime_list[x]

    MAX = 10000
    squares = dict.fromkeys((x*x for x in xrange(1, MAX)), 1)
    _refresh(MAX)

    for x in xrange(35, MAX, 2):
        if not _isprime(x):
            is_goldbach = 0
            for p in prime_list[1:]:
                if p >= x: break
                if squares.has_key((x - p)/2):
                    is_goldbach = 1
                    break
            if not is_goldbach:
                return x
                break

