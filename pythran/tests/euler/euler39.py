#runas solve(1000)
#pythran export solve(int)
def solve(n):
    '''
    If p is the perimeter of a right angle triangle with integral length sides, {a,b,c}, there are exactly three solutions for p = 120.
    
    {20,48,52}, {24,45,51}, {30,40,50}
    
    For which value of p < 1000, is the number of solutions maximised?
    '''

    maxp, maxsol = 0, 0
    for p in xrange(12, n + 1, 2):
        solutions = 0
        # a < b < c. So a is at most 1/3 of p. b is between a and (p-a)/2
        for a in xrange(1, p/3):
            a2 = a*a
            for b in xrange(a, (p-a)/2):
                c = p - a - b
                if a2 + b*b == c*c: solutions = solutions + 1
        if solutions > maxsol: maxp, maxsol = p, solutions

    return maxp
