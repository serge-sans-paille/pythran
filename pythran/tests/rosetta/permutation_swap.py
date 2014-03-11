#from http://rosettacode.org/wiki/Permutations_by_swapping#Python
#pythran export test()
#runas test()
#unittest.skip requires two-step typing

def s_permutations(seq):
    items = [[]]
    for j in seq:
        new_items = []
        for i, item in enumerate(items):
            if i % 2:
                # step up
                new_items += [item[:i] + [j] + item[i:]
                    for i in range(len(item) + 1)]
            else:
                # step down
                new_items += [item[:i] + [j] + item[i:]
                    for i in range(len(item), -1, -1)]
        items = new_items

    return [(tuple(item), -1 if i % 2 else 1)
        for i, item in enumerate(items)]

def test():
    for n in (3, 4):
        print '\nPermutations and sign of %i items' % n
        for i in s_permutations(range(n)):
            print 'Perm: ', i
