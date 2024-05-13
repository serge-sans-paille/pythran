#pythran export b(int)
import numpy
def b(n): return numpy.ones((n, n)) @ numpy.ones((n, n))

