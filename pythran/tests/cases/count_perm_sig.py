#from: https://www.youtube.com/watch?v=LBht4RO3-qs&list=UU5-umfrfqPvDvWCYHJGYtpA
#runas count_perm_sig(1000, 3, 3)


#pythran export count_perm_sig(int, int, int)

import random as rd

def count_perm_sig(n, s, k):
    rd.seed(s)
    myset = set()
    count = 0
    permutation = [i for i in range(k)]
    for i in range(n):
        rd.shuffle(permutation)
        sig = signature(permutation) 
        if sig not in myset:
            myset.add(sig)
            count += 1
    return myset, count

def signature(perm):
    i = perm.index(0)
    sig_1 = perm[i:]+perm[:i]
    sig_2 = sig_1[0:1]+sig_1[1:][::-1]

    if sig_1[1] < sig_2[1]:
        sig = sig_1
    else:
        sig = sig_2

    return tuple(sig)
