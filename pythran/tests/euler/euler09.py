#pythran export solve(int)
#runas solve(1000)
def solve(v):
    '''
    A Pythagorean triplet is a set of three natural numbers, a  b  c, for which,
    a^2 + b^2 = c^2
    For example, 3^2 + 4^2 = 9 + 16 = 25 = 5^2.
    
    There exists exactly one Pythagorean triplet for which a + b + c = 1000.
    Find the product abc.
    '''

    for a in xrange(1, v):
        for b in xrange(a, v):
            c = v - a - b
            if c > 0:
                if c*c == a*a + b*b:
                    return a*b*c
