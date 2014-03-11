#from http://rosettacode.org/wiki/Permutation_test#Python
#pythran export permutationTest(int list, int list)
#pythran export permutationTest2(int list, int list)
#runas permutationTest([85, 88, 75, 66, 25, 29, 83, 39, 97], [68, 41, 10, 49, 16, 65, 32, 92, 28, 98])
#runas permutationTest2([85, 88, 75, 66, 25, 29, 83, 39, 97], [68, 41, 10, 49, 16, 65, 32, 92, 28, 98])
from itertools import combinations as comb

def statistic(ab, a):
    sumab, suma = sum(ab), sum(a)
    return ( suma / len(a) - (sumab -suma) / (len(ab) - len(a)) )

def permutationTest(a, b):
    ab = a + b
    Tobs = statistic(ab, a)
    under = 0
    for count, perm in enumerate(comb(ab, len(a)), 1):
        if statistic(ab, perm) <= Tobs:
            under += 1
    return under * 100. / count

def permutationTest2(a, b):
    ab = a + b
    Tobs = sum(a)
    under = 0
    for count, perm in enumerate(comb(ab, len(a)), 1):
        if sum(perm) <= Tobs:
            under += 1
    return under * 100. / count
