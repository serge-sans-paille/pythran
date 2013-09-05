#runas solve()
#unittest.skip recursive generator
#pythran export solve()
def solve():
    '''
    In England the currency is made up of pound, P, and pence, p, and there are eight coins in general circulation:

    1p, 2p, 5p, 10p, 20p, 50p, P1 (100p) and P2 (200p).
    It is possible to make P2 in the following way:

    1 P1 + 1 50p + 2 20p + 1 5p + 1 2p + 3 1p
    How many different ways can P2 be made using any number of coins?
    '''

    coins = [1, 2, 5, 10, 20, 50, 100, 200]

    def balance(pattern): return sum(coins[x]*pattern[x] for x in xrange(0, len(pattern)))

    def gen(pattern, coinnum, num):
        coin = coins[coinnum]
        for p in xrange(0, num/coin + 1):
            newpat = pattern[:coinnum] + (p,)
            bal = balance(newpat)
            if bal > num: return
            elif bal == num: yield newpat
            elif coinnum < len(coins)-1:
                for pat in gen(newpat, coinnum+1, num):
                    yield pat

    return sum(1 for pat in gen((), 0, 200))


