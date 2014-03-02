#unittest.skip import combinatorics
'''
The product 7254 is unusual, as the identity, 39 x 186 = 7254, containing multiplicand, multiplier, and product is 1 through 9 pandigital.

Find the sum of all products whose multiplicand/multiplier/product identity can be written as a 1 through 9 pandigital.

HINT: Some products can be obtained in more than one way so be sure to only include it once in your sum.
'''

from combinatorics import permutations

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

print sum(p for p in product)
