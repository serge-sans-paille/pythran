#unittest.skip recursive generator
#pythran export solve()
def solve():
    '''
    By replacing the 1st digit of *57, it turns out that six of the possible values: 157, 257, 457, 557, 757, and 857, are all prime.
    
    By replacing the 3rd and 4th digits of 56**3 with the same digit, this 5-digit number is the first example having seven primes, yielding the family: 56003, 56113, 56333, 56443, 56663, 56773, and 56993. Consequently 56003, being the first member of this family, is the smallest prime with this property.
    
    Find the smallest prime which, by replacing part of the number (not necessarily adjacent digits) with the same digit, is part of an eight prime value family.
    '''
    
    import prime
    from combinatorics import uniqueCombinations
    
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

