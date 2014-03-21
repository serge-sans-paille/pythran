#pythran export solve(int)
#runas solve(10001)
def solve(p):
    '''
    By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.

    What is the 10001st prime number?
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

    def prime(x):
        ''' Returns the xth prime '''

        lastn = prime_list[-1]
        while len(prime_list) <= x:                 # Keep working until we've got the xth prime
            lastn = lastn + 1                       # Check the next number
            if _isprime(lastn):
                prime_list.append(lastn)            # Maintain a list for sequential access
        return prime_list[x]

    return prime(p - 1)
