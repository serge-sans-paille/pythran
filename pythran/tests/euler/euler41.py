#pythran export solve()
def solve():
    '''
    We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n exactly once. For example, 2143 is a 4-digit pandigital and is also prime.
    
    What is the largest n-digit pandigital prime that exists?
    '''
    
    import prime
    from combinatorics import permutations
    
    # Pan-digital primes are 4 or 7 digits. Others divisible by 3
    prime._refresh(2766)    # sqrt(7654321)
    for perm in permutations(range(7, 0, -1)):
        num = 0
        for n in perm: num = num * 10 + n
        if prime._isprime(num):
            print num
            break
