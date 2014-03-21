#pythran export solve(int, int)
#runas solve(1, 20)
def solve(start, end):
    '''
    2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.
    
    What is the smallest number that is evenly divisible by all of the numbers from 1 to 20?
    '''
    def gcd(a,b): return b and gcd(b, a % b) or a
    def lcm(a,b): return a * b / gcd(a,b)

    n = 1
    for i in xrange(start, end + 1):
        n = lcm(n, i)

    return n
