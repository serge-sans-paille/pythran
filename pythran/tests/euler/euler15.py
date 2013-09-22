#runas solve()
#pythran export solve()
def solve():
    def fact(n):
        f = 1L
        for x in xrange(1, n+1): f = f * x
        return f

    return fact(40) / fact(20) / fact(20)

