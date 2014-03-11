#from http://rosettacode.org/wiki/Permutations/Rank_of_a_permutation#Python
#pythran export test()
#runas test()
from math import factorial as fact
from random import randrange

def identity_perm(n):
    return list(range(n))

def unranker1(n, r, pi):
    while n > 0:
        n1, (rdivn, rmodn) = n-1, divmod(r, n)
        pi[n1], pi[rmodn] = pi[rmodn], pi[n1]
        n = n1
        r = rdivn
    return pi

def init_pi1(n, pi):
    pi1 = [-1] * n
    for i in range(n):
        pi1[pi[i]] = i
    return pi1

def ranker1(n, pi, pi1):
    if n == 1:
        return 0
    n1 = n-1
    s = pi[n1]
    pi[n1], pi[pi1[n1]] = pi[pi1[n1]], pi[n1]
    pi1[s], pi1[n1] = pi1[n1], pi1[s]
    return s + n * ranker1(n1, pi, pi1)

def unranker2(n, r, pi):
    while n > 0:
        n1 = n-1
        s, rmodf = divmod(r, fact(n1))
        pi[n1], pi[s] = pi[s], pi[n1]
        n = n1
        r = rmodf
    return pi

def ranker2(n, pi, pi1):
    if n == 1:
        return 0
    n1 = n-1
    s = pi[n1]
    pi[n1], pi[pi1[n1]] = pi[pi1[n1]], pi[n1]
    pi1[s], pi1[n1] = pi1[n1], pi1[s]
    return s * fact(n1) + ranker2(n1, pi, pi1)

def get_random_ranks(permsize, samplesize):
    perms = fact(permsize)
    ranks = set()
    while len(ranks) < samplesize:
        ranks |= set( randrange(perms)
                      for r in range(samplesize - len(ranks)) )
    return ranks

def test1(comment, unranker, ranker):
    n, samplesize, n2 = 3, 4, 12
    print(comment)
    perms = []
    for r in range(fact(n)):
        pi = identity_perm(n)
        perm = unranker(n, r, pi)
        perms.append((r, perm))
    for r, pi in perms:
        pi1 = init_pi1(n, pi)
        print('  From rank %s to %s back to %s' % (r, pi, ranker(n, pi[:], pi1)))
    print('\n  %s random individual samples of %s items:' % (samplesize, n2))
    for r in get_random_ranks(n2, samplesize):
        pi = identity_perm(n2)
        print('    ' + ' '.join('%s' % i for i in unranker(n2, r, pi)))
    print('')

def test2(comment, unranker):
    samplesize, n2 = 4, 20
    print(comment)
    print('  %s random individual samples of %s items:' % (samplesize, n2))
    txt = ''
    for r in get_random_ranks(n2, samplesize):
        pi = identity_perm(n2)
        txt += '\n' + ''.join(str(unranker(n2, r, pi)))
    print(txt, '')

def test():
    test1('First ordering:', unranker1, ranker1)
    test1('Second ordering:', unranker2, ranker2)
    test2('First ordering, large number of perms:', unranker1)
