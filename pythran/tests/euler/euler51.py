#runas solve()
#unittest.skip recursive generator
#pythran export solve()
def solve():
    '''
    By replacing the 1st digit of *57, it turns out that six of the possible values: 157, 257, 457, 557, 757, and 857, are all prime.
    
    By replacing the 3rd and 4th digits of 56**3 with the same digit, this 5-digit number is the first example having seven primes, yielding the family: 56003, 56113, 56333, 56443, 56663, 56773, and 56993. Consequently 56003, being the first member of this family, is the smallest prime with this property.
    
    Find the smallest prime which, by replacing part of the number (not necessarily adjacent digits) with the same digit, is part of an eight prime value family.
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
                prime_list.append(lastn)            # Maintain a list for sequential access

    def prime(x):
        ''' Returns the xth prime '''
        while len(prime_list) <= x:                 # Keep working until we've got the xth prime
            lastn = lastn + 1                       # Check the next number
            if _isprime(lastn):
                prime_list.append(lastn)            # Maintain a list for sequential access
        return prime_list[x]

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

    def uniqueCombinations(items, n):
        ''' take n distinct items, order is irrelevant '''
        def afterIthItem(items, i):
            return items[i+1:]
        return _combinators(afterIthItem, items, n)

    cache = {}
    def prime_family_length(n, digits):
        if cache.has_key((n, digits)): return cache[n, digits]

        num, nums, count = list(str(n)), [], 0
        if len(dict.fromkeys(num[d] for d in digits).keys()) > 1:
            return cache.setdefault((n, digits), 0)                                # The digits must have the same number

        for d in range(0 in digits and 1 or 0, 10):                                 # Ensure 0 is not the first digit
            for x in digits: num[x] = str(d)
            n = int(''.join(num))
            if prime.isprime(n): count += 1
            nums.append(n)
        for n in nums: cache[n, digits] = count
        return count

    prime._refresh(100000)

    n, max, max_count, combos = 10, 0, 0, {}
    while max_count < 8:
        p = prime.prime(n)
        digits = range(0, len(str(p)))
        for size in xrange(1, len(digits)):
            patterns = combos.setdefault((len(digits), size),
                tuple(tuple(sorted(p)) for p in uniqueCombinations(digits, size)))
            for pat in patterns:
                count = prime_family_length(p, pat)
                if count > max_count: max, max_count = p, count
        n += 1

    return p
