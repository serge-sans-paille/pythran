#from http://rosettacode.org/wiki/Generator/Exponential#Python
#pythran export test(int, int)
#runas test(2, 3)

#FIXME unittest.skip

from itertools import islice, count

def powers(m):
    for n in count():
        yield n ** m

def filtered(s1, s2):
    v, f = next(s1), next(s2)
    while True:
        if v > f:
            f = next(s2)
            continue
        elif v < f:
            yield v
        v = next(s1)

def test(sq, cu):
    squares, cubes = powers(sq), powers(cu)
    f = filtered(squares, cubes)
    return list(islice(f, 20, 30))
