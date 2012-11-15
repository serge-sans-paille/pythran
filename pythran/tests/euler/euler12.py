
#pythran export solve()
def solve():
    import prime
    for i in xrange(1, 1000000000):
        n = i * (i+1) / 2
        if prime.num_factors(n) > 500:
            return n
            break

