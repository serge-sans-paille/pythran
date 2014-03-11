#from http://rosettacode.org/wiki/Prime_decomposition#Python
#pythran export fac(int)
#runas fac(2**59 - 1)
#pythran export test_decompose(int)
#runas test_decompose(2**59 - 1)
import math

def decompose(n):
    primelist = [2, 3]
    for p in primes(primelist):
        if p*p > n: break
        while n % p == 0:
            yield p
            n /=p
    if n > 1:
        yield n

def test_decompose(to):
    return [i for i in decompose(to)]

def primes(primelist):
    for n in primelist: yield n

    n = primelist[-1]
    while True:
        n += 2
        for x in primelist:
            if not n % x: break
            if x * x > n:
                primelist.append(n)
                yield n
                break

def fac(n):
    step = lambda x: 1 + x*4 - (x/2)*2
    maxq = long(math.floor(math.sqrt(n)))
    d = 1
    q = n % 2 == 0 and 2 or 3
    while q <= maxq and n % q != 0:
        q = step(d)
        d += 1
    res = []
    if q <= maxq:
        res.extend(fac(n//q))
        res.extend(fac(q))
    else: res=[n]
    return res
