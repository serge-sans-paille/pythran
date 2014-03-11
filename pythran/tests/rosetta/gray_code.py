#from http://rosettacode.org/wiki/Gray_code
#pythran export bin2gray(int list)
#pythran export gray2bin(int list)
#pythran export int2bin(int)
#pythran export bin2int(int list)
#runas [int2bin(i) for i in xrange(16)]
#runas [bin2gray(int2bin(i)) for i in xrange(16)]
#runas [gray2bin(bin2gray(int2bin(i))) for i in xrange(16)]
#runas [bin2int(gray2bin(bin2gray(int2bin(i)))) for i in xrange(16)]

def bin2gray(bits):
    return bits[:1] + [i ^ ishift for i, ishift in zip(bits[:-1], bits[1:])]

def gray2bin(bits):
    b = [bits[0]]
    for nextb in bits[1:]: b.append(b[-1] ^ nextb)
    return b


def int2bin(n):
    'From positive integer to list of binary bits, msb at index 0'
    if n:
        bits = []
        while n:
            n,remainder = divmod(n, 2)
            bits.insert(0, remainder)
        return bits
    else: return [0]


def bin2int(bits):
    'From binary bits, msb at index 0 to integer'
    i = 0
    for bit in bits:
        i = i * 2 + bit
    return i
