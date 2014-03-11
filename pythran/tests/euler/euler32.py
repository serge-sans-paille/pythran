#runas solve()
#unittest.skip recursive generator
#pythran export solve()

''' From O'Reilly's Python Cookbook '''

def _combinators(_handle, items, n):
    if n==0:
        yield []
        return
    for i, item in enumerate(items):
        this_one = [ item ]
        for cc in _combinators(_handle, _handle(items, i), n-1):
            yield this_one + cc

def combinations(items, n):
    ''' take n distinct items, order matters '''
    def skipIthItem(items, i):
        return items[:i] + items[i+1:]
    return _combinators(skipIthItem, items, n)

def uniqueCombinations(items, n):
    ''' take n distinct items, order is irrelevant '''
    def afterIthItem(items, i):
        return items[i+1:]
    return _combinators(afterIthItem, items, n)

def selections(items, n):
    ''' take n (not necessarily distinct) items, order matters '''
    def keepAllItems(items, i):
        return items
    return _combinators(keepAllItems, items, n)

def permutations(items):
    ''' take all items, order matters '''
    return combinations(items, len(items))

def solve():
    '''
    The product 7254 is unusual, as the identity, 39 x 186 = 7254, containing multiplicand, multiplier, and product is 1 through 9 pandigital.

    Find the sum of all products whose multiplicand/multiplier/product identity can be written as a 1 through 9 pandigital.

    HINT: Some products can be obtained in more than one way so be sure to only include it once in your sum.
    '''

    ''' From O'Reilly's Python Cookbook '''


    def num(l):
        s = 0
        for n in l: s = s * 10 + n
        return s

    product = {}
    for perm in permutations(range(1,10)):
        for cross in range(1,4):            # Number can't be more than 4 digits
            for eq in range(cross+1, 6):    # Result can't be less than 4 digits
                a = num(perm[0:cross])
                b = num(perm[cross:eq])
                c = num(perm[eq:9])
                if a * b == c: product[c] = 1

    return sum(p for p in product)

