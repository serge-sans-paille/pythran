#pythran export solve()
def solve():
    def fact(n):
        f = 1
        for x in xrange(1, n+1): f = f * x
        return f

    print fact(40) / fact(20) / fact(20)
