#unittest.skip recursive generator
#pythran export solve()
def solve():
    '''
    The arithmetic sequence, 1487, 4817, 8147, in which each of the terms increases by 3330, is unusual in two ways: (i) each of the three terms are prime, and, (ii) each of the 4-digit numbers are permutations of one another.
    
    There are no arithmetic sequences made up of three 1-, 2-, or 3-digit primes, exhibiting this property, but there is one other 4-digit increasing sequence.
    
    What 12-digit number do you form by concatenating the three terms in this sequence?
    
    '''
    
    import prime
    from combinatorics import permutations
    
    prime._refresh(10000)
    for num in xrange(1000, 10000):
        if str(num).find('0') >= 0: continue
    
        if prime.isprime(num):
            prime_permutations = { num: 1 }
            for x in permutations(list(str(num))):
                next_num = int(''.join(x))
                if prime.isprime(next_num):
                    prime_permutations[next_num] = 1
    
            primes = sorted(prime_permutations.keys())
            for a in xrange(0, len(primes)):
                if primes[a] == 1487: continue
                for b in xrange(a+1, len(primes)):
                    c = (primes[a] + primes[b]) / 2
                    if prime_permutations.has_key(c):
                        return str(primes[a]) + str(c) + str(primes[b])
                        exit()

