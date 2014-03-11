#from http://rosettacode.org/wiki/Harshad_or_Niven_series#Python
#pythran export test()
#runas test()
#FIXME unittest.skip

import itertools
def harshad():
    for n in itertools.count(1):
        if n % sum(int(ch) for ch in str(n)) == 0:
            yield n

def test():
    l = list(itertools.islice(harshad(), 0, 20))
    for n in harshad():
        if n > 1000:
            r = n
            break

    from itertools import count, islice
    harshad_ = (n for n in count(1) if n % sum(int(ch) for ch in str(n)) == 0)
    l2 = list(islice(harshad_, 0, 20))
    r2  = next(x for x in harshad_ if x > 1000)
    return r,l, r2, l2
