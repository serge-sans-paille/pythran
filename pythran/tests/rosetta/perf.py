#from http://rosettacode.org/wiki/Perfect_numbers#Python
#pythran export perf(int)
#pythran export perf_(int)
#runas map(perf, range(20))
#runas map(perf_, range(20))

def perf(n):
    sum = 0
    for i in xrange(1, n):
        if n % i == 0:
            sum += i
    return sum == n

def perf_(n):
    return n == sum(i for i in xrange(1, n) if n % i == 0)
