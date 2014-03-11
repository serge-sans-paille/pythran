#from http://rosettacode.org/wiki/Primality_by_trial_division#Python
#pythran exprot test()
#runas test()
#FIXME unittest.skip

def prime(a):
    return not (a < 2 or any(a % x == 0 for x in xrange(2, int(a**0.5) + 1)))

def prime2(a):
    if a == 2: return True
    if a < 2 or a % 2 == 0: return False
    return not any(a % x == 0 for x in xrange(3, int(a**0.5) + 1, 2))

def prime3(a):
    if a < 2: return False
    if a == 2 or a == 3: return True # manually test 2 and 3   
    if a % 2 == 0 or a % 3 == 0: return False # exclude multiples of 2 and 3

    maxDivisor = a**0.5
    d, i = 5, 2
    while d <= maxDivisor:
        if a % d == 0: return False
        d += i
        i = 6 - i # this modifies 2 into 4 and viceversa

    return True

def test():
    return [i for i in range(40) if prime(i)], [i for i in range(40) if prime2(i)], [i for i in range(40) if prime3(i)]
