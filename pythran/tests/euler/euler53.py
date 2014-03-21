#runas solve(1000000)
#pythran export solve(int)
def solve(m):
    '''
    There are exactly ten ways of selecting three from five, 12345:
    
    123, 124, 125, 134, 135, 145, 234, 235, 245, and 345
    
    In combinatorics, we use the notation, 5C3 = 10.
    
    In general,
    
    nCr = n! / r!(nr)! where r <= n, n! = n x (n-1)...x 3 x 2 x 1, and 0! = 1.
    
    It is not until n = 23, that a value exceeds one-million: 23C10 = 1144066.
    
    How many, not necessarily distinct, values of  nCr, for 1 <= n <= 100, are greater than one-million?
    '''

    fact_c = { 0: 1L, 1: 1L }
    def fact(n): return fact_c.has_key(n) and fact_c[n] or fact_c.setdefault(n, n * fact(n-1))

    count = 0
    for n in xrange(1, 101):
        for r in xrange(0, n):
            ncr = fact(n) / fact(r) / fact(n-r)
            if ncr > m: count += 1
    return count

