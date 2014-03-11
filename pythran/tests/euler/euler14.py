#runas solve(1000000)
#pythran export solve(int)
def solve(max_init):
    cache = { 1: 1 }
    def chain(cache, n):
        if not cache.get(n,0):
            if n % 2: cache[n] = 1 + chain(cache, 3*n + 1)
            else: cache[n] = 1 + chain(cache, n/2)
        return cache[n]

    m,n = 0,0
    for i in xrange(1, max_init):
        c = chain(cache, i)
        if c > m: m,n = c,i

    return n

