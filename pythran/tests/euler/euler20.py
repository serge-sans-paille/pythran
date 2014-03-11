#runas solve(100)
#pythran export solve(int)
def solve(v):
    '''
    Find the sum of digits in 100!
    '''

    def digits(n):
        s = 0
        while n > 0:
            s = s + (n % 10)
            n = n / 10
        return s

    n = 1L
    for i in xrange(1,v): n = n*i
    return digits(n)

