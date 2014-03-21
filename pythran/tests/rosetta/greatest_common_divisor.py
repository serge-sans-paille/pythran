#from http://rosettacode.org/wiki/Greatest_common_divisor#Python
#pythran export gcd_iter(int, int)
#pythran export gcd(int, int)
#pythran export gcd_bin(int, int)
#runas gcd_iter(40902, 24140)
#runas gcd(40902, 24140)
#runas gcd_bin(40902, 24140)

def gcd_iter(u, v):
    while v:
        u, v = v, u % v
    return abs(u)

def gcd(u, v):
    return gcd(v, u % v) if v else abs(u)

def gcd_bin(u, v):
    u, v = abs(u), abs(v) # u >= 0, v >= 0
    if u < v:
        u, v = v, u # u >= v >= 0
    if v == 0:
        return u

    # u >= v > 0
    k = 1
    while u & 1 == 0 and v & 1 == 0: # u, v - even
        u >>= 1; v >>= 1
        k <<= 1

    t = -v if u & 1 else u
    while t:
        while t & 1 == 0:
            t >>= 1
        if t > 0:
            u = t
        else:
            v = -t
        t = u - v
    return u * k
