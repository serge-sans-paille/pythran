import numpy as np

#pythran export rosen(float[])

def rosen(x):
    t0 = 100 * (x[1:] - x[:-1] ** 2) ** 2
    t1 = (1 - x[:-1]) ** 2
    return np.sum(t0 + t1)

#pythran export rosen2(float[])

def rosen2(x):
    return np.sum(100 * (x[1:] - x[:-1] ** 2) ** 2 + (1 - x[:-1]) ** 2)

#    a = numpy.arange(100000)

#    CPython
#    In [5]: %timeit -n100 rosen.rosen(a)
#    100 loops, best of 3: 1.64 ms per loop
#
#    In [6]: %timeit -n100 rosen.rosen2(a)
#    100 loops, best of 3: 1.38 ms per loop
#
#    In [7]: %timeit -n100 rosen.rosen2(a)
#    100 loops, best of 3: 1.37 ms per loop
#
#    In [8]: %timeit -n100 rosen.rosen(a)
#    100 loops, best of 3: 1.62 ms per loop
#
#    Pythran
#    In [7]: %timeit -n100 rosen.rosen(a)
#    100 loops, best of 3: 494 us per loop
#    
#    In [8]: %timeit -n100 rosen.rosen(a)
#    100 loops, best of 3: 495 us per loop
#    
#    In [9]: %timeit -n100 rosen.rosen2(a)
#    100 loops, best of 3: 201 us per loop
#    
#    In [10]: %timeit -n100 rosen.rosen2(a)
#    100 loops, best of 3: 201 us per loop
#
#     Pytran SIMD
#     In [4]: %timeit -n100 rosen.rosen(a)
#     100 loops, best of 3: 414 us per loop
#     
#     In [6]: %timeit -n100 rosen.rosen(a)
#     100 loops, best of 3: 415 us per loop
#     
#     In [7]: %timeit -n100 rosen.rosen2(a)
#     100 loops, best of 3: 244 us per loop

#     In [5]: %timeit -n100 rosen.rosen2(a)
#     100 loops, best of 3: 245 us per loop
#     
#
#    
#    
#   Pythran with lazy
#    In [4]: %timeit -n100 rosen.rosen(a)
#    100 loops, best of 3: 287 us per loop
#    
#    In [5]: %timeit -n100 rosen.rosen(a)
#    100 loops, best of 3: 288 us per loop
#    
#    In [6]: %timeit -n100 rosen.rosen2(a)
#    100 loops, best of 3: 201 us per loop
#    
#    In [7]: %timeit -n100 rosen.rosen2(a)
#    100 loops, best of 3: 201 us per loop
#    
