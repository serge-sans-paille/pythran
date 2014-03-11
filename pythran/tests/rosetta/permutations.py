#from http://rosettacode.org/wiki/Permutations#Python
#pythran export test(int)
#runas test(3)

def test(n):
    import itertools
    return [values for values in itertools.permutations(range(1, n + 1))]
