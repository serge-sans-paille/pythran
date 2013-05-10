#from http://rosettacode.org/wiki/Perfect_numbers#Python
def perf(n):
    sum = 0
    for i in xrange(1, n):
        if n % i == 0:
            sum += i
    return sum == n


def test():
    print map(perf, range(20))
    perf_ = lambda n: n == sum(i for i in xrange(1, n) if n % i == 0)
    print map(perf_, range(20))
