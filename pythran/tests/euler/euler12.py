#runas solve(500)
#pythran export solve(int)
def solve(nfact):

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

    def prime(x):
        ''' Returns the xth prime '''

        lastn = prime_list[-1]
        while len(prime_list) <= x:                 # Keep working until we've got the xth prime
            lastn = lastn + 1                       # Check the next number
            if _isprime(lastn):
                prime_list.append(lastn)            # Maintain a list for sequential access
        return prime_list[x]

    def num_factors(n):
        ''' Returns the number of factors of n, including 1 and n '''
        div = 1
        x = 0
        while n > 1:
            c = 1
            while not n % prime(x):
                c = c + 1
                n = n / prime(x)
            x = x + 1
            div = div * c
        return div

    for i in xrange(1, 1000000000):
        n = i * (i+1) / 2
        if num_factors(n) > nfact:
            return n
            break

