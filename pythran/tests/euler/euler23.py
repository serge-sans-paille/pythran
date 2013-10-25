#runas solve()
#unittest.skip recursive generators
#pythran export solve()
'''
 A perfect number is a number for which the sum of its proper divisors is exactly equal to the number. For example, the sum of the proper divisors of 28 would be 1 + 2 + 4 + 7 + 14 = 28, which means that 28 is a perfect number.

 A number whose proper divisors are less than the number is called deficient and a number whose proper divisors exceed the number is called abundant.

 As 12 is the smallest abundant number, 1 + 2 + 3 + 4 + 6 = 16, the smallest number that can be written as the sum of two abundant numbers is 24. By mathematical analysis, it can be shown that all integers greater than 28123 can be written as the sum of two abundant numbers. However, this upper limit cannot be reduced any further by analysis even though it is known that the greatest number that cannot be expressed as the sum of two abundant numbers is less than this limit.

 Find the sum of all the positive integers which cannot be written as the sum of two abundant numbers.
 '''

def solve():
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
        ''' Refreshes primes upto x '''
        lastn = prime_list[-1]
        while lastn <= x:                           # Keep working until we've got up to x
            lastn = lastn + 1                       # Check the next number
            if _isprime(lastn):
                prime_list.append(lastn)            # Maintain a list for sequential access

    def factors(n):
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

    def all_factors(n):
        ''' Returns all factors of n, including 1 and n '''
        f = factors(n)
        elts = sorted(set(f))
        numelts = len(elts)
        def gen_inner(i):
            if i >= numelts:
                yield 1
                return
            thiselt = elts[i]
            thismax = f.count(thiselt)
            powers = [1]
            for j in xrange(thismax):
                powers.append(powers[-1] * thiselt)
            for d in gen_inner(i+1):
                for prime_power in powers:
                    yield prime_power * d
        for d in gen_inner(0):
            yield d

    MAX = 28124
    _refresh(MAX/2)
    abundants = [n for n in xrange(1, MAX) if sum(all_factors(n)) > n+n]
    abundants_dict = dict.fromkeys(abundants, 1)

    total = 0
    for n in xrange(1, MAX):
        sum_of_abundants = 0
        for a in abundants:
            if a > n: break
            if abundants_dict.get(n - a):
                sum_of_abundants = 1
                break
            if not sum_of_abundants:
                total = total + n

    return total
