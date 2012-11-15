#pythran export solve()
def solve():
    '''
    The number, 1406357289, is a 0 to 9 pandigital number because it is made up of each of the digits 0 to 9 in some order, but it also has a rather interesting sub-string divisibility property.
    
    Let d1 be the 1st digit, d2 be the 2nd digit, and so on. In this way, we note the following:
    
    d2 d3 d4 = 406 is divisible by 2
    d3 d4 d5 = 063 is divisible by 3
    d4 d5 d6 = 635 is divisible by 5
    d5 d6 d7 = 357 is divisible by 7
    d6 d7 d8 = 572 is divisible by 11
    d7 d8 d9 = 728 is divisible by 13
    d8 d9 d10= 289 is divisible by 17
    
    Find the sum of all 0 to 9 pandigital numbers with this property.
    '''
    
    from combinatorics import permutations
    
    def num(l):
        s = 0
        for n in l: s = s * 10 + n
        return s
    
    def subdiv(l, n): return num(l) % n == 0
    
    total = 0
    for perm in permutations((0,1,2,3,4,6,7,8,9)):
        perm.insert(5, 5)               # d6 must be 5
        if (subdiv(perm[7:10], 17) and
            subdiv(perm[6:9],  13) and
            subdiv(perm[5:8],  11) and
            subdiv(perm[4:7],   7) and
            subdiv(perm[3:6],   5) and
            subdiv(perm[2:5],   3) and
            subdiv(perm[1:4],   2)):
                total += num(perm)
    
    print total
