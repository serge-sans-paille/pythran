#from http://rosettacode.org/wiki/Hailstone_sequence#Python
#pythran export hailstone(int)
#runas hailstone(27)
#runas max((len(hailstone(i)), i) for i in range(1,100000))

def hailstone(n):
    seq = [n]
    while n>1:
        n = 3*n + 1 if n & 1 else n//2
        seq.append(n)
    return seq
