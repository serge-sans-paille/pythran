# from http://stackoverflow.com/questions/3939660/sieve-of-eratosthenes-finding-primes-python
# using a list instead of generator as return values

#pythran export primes_sieve(int)
def primes_sieve(limit):
    a = [True] * limit                          # Initialize the primality list
    a[0] = a[1] = False
    primes=list()

    for (i, isprime) in enumerate(a):
        if isprime:
            primes.append(i)
            for n in xrange(i*i, limit, i):     # Mark factors non-prime
                a[n] = False

    return primes
