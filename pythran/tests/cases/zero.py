#pythran export zero(int, int)
#runas zero(10,20)
#bench zero(6000,6000)
def zero(n,m): return [[0 for row in xrange(n)] for col in xrange(m)]

