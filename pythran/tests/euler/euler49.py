#runas solve()
#unittest.skip recursive generator
#pythran export solve()
def solve():
    '''
    The arithmetic sequence, 1487, 4817, 8147, in which each of the terms increases by 3330, is unusual in two ways: (i) each of the three terms are prime, and, (ii) each of the 4-digit numbers are permutations of one another.
    
    There are no arithmetic sequences made up of three 1-, 2-, or 3-digit primes, exhibiting this property, but there is one other 4-digit increasing sequence.
    
    What 12-digit number do you form by concatenating the three terms in this sequence?
    
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
        ''' Refreshes primes upto x '''
        while lastn <= x:                           # Keep working until we've got up to x
            lastn = lastn + 1                       # Check the next number
            if _isprime(lastn):
                prime_list.append(lastn) 
    def isprime(x):
        ''' Returns 1 if x is prime, 0 if not. Uses a pre-computed dictionary '''
        _refresh(x)                                 # Compute primes up to x (which is a bit wasteful)
        return prime_dict.get(x, 0) 
    
    def _combinators(_handle, items, n):
        if n==0:
            yield []
            return
        for i, item in enumerate(items):
            this_one = [ item ]
            for cc in _combinators(_handle, _handle(items, i), n-1):
                yield this_one + cc

    def combinations(items, n):
        ''' take n distinct items, order matters '''
        def skipIthItem(items, i):
            return items[:i] + items[i+1:]
        return _combinators(skipIthItem, items, n)

    def permutations(items):
        ''' take all items, order matters '''
        return combinations(items, len(items))
    
    _refresh(10000)
    for num in xrange(1000, 10000):
        if str(num).find('0') >= 0: continue
    
        if isprime(num):
            prime_permutations = { num: 1 }
            for x in permutations(list(str(num))):
                next_num = int(''.join(x))
                if isprime(next_num):
                    prime_permutations[next_num] = 1
    
            primes = sorted(prime_permutations.keys())
            for a in xrange(0, len(primes)):
                if primes[a] == 1487: continue
                for b in xrange(a+1, len(primes)):
                    c = (primes[a] + primes[b]) / 2
                    if prime_permutations.has_key(c):
                        return str(primes[a]) + str(c) + str(primes[b])
                        exit()

