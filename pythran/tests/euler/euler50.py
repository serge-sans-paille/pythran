#runas solve(1000000)
#pythran export solve(int)
def solve(m):
    '''
    The prime 41, can be written as the sum of six consecutive primes:
    
    41 = 2 + 3 + 5 + 7 + 11 + 13
    This is the longest sum of consecutive primes that adds to a prime below one-hundred.
    
    The longest sum of consecutive primes below one-thousand that adds to a prime, contains 21 terms, and is equal to 953.
    
    Which prime, below one-million, can be written as the sum of the most consecutive primes?
    '''
    prime_list = [2, 3, 5, 7, 11, 13, 17, 19, 23]   # Ensure that this is initialised with at least 1 prime
    prime_dict = dict.fromkeys(prime_list, 1)
    lastn      = prime_list[-1]
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
        lastn      = prime_list[-1]
        ''' Refreshes primes upto x '''
        while lastn <= x:                           # Keep working until we've got up to x
            lastn = lastn + 1                       # Check the next number
            if _isprime(lastn):
                prime_list.append(lastn)            # Maintain a list for sequential access

    def prime(x):
        ''' Returns the xth prime '''
        lastn      = prime_list[-1]
        while len(prime_list) <= x:                 # Keep working until we've got the xth prime
            lastn = lastn + 1                       # Check the next number
            if _isprime(lastn):
                prime_list.append(lastn)            # Maintain a list for sequential access
        return prime_list[x]

    def isprime(x):
        ''' Returns 1 if x is prime, 0 if not. Uses a pre-computed dictionary '''
        _refresh(x)                                 # Compute primes up to x (which is a bit wasteful)
        return prime_dict.get(x, 0)

    MAX = 5000
    prime(MAX)

    def check_length(n, below):
        maxprime = 0
        for x in xrange(0, below):
            total = sum(prime_list[x:x+n])
            if total > below: break
            if isprime(total): maxprime = total
        return maxprime

    for n in xrange(1000, 0, -1):
        maxprime = check_length(n, m)
        if maxprime:
            return maxprime
            break

