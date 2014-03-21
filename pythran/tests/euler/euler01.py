#pythran export solve(int)
#runas solve(1000)
def solve(max):
    '''
    If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9. The sum of these multiples is 23.

    Find the sum of all the multiples of 3 or 5 below 1000.
    '''

    n = 0
    for i in xrange(1, max):
        if not i % 5 or not i % 3:
            n = n + i

    return n
