#from http://stackoverflow.com/questions/19350395/python-jit-for-known-bottlenecks
#pythran export gf2mulmod(long, long, long)
#runas x, y, m = 2**1024 , 2**65-1, 2**67-1; gf2mulmod(x, y, m)

def gf2mulmod(x,y,m):
    z = 0
    while x > 0:
        if (x & 1) != 0:
            z ^= y
        y <<= 1
        y2 = y ^ m
        if y2 < y:
            y = y2
        x >>= 1
    return z
