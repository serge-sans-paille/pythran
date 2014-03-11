#runas solve()
#pythran export solve()
def solve():
    '''
    Find the last ten digits of the series, 1^1 + 2^2 + 3^3 + ... + 1000^1000.
    '''

    s = 0L
    mod = pow(10, 10)
    for x in xrange(1, 1001):
        s = s + pow(long(x), x)

    return s % mod

