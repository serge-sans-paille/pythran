#runas solve(100)
#pythran export solve(int)
def solve(max):
    '''
    The sum of the squares of the first ten natural numbers is,
    1^2 + 2^2 + ... + 10^2 = 385
    The square of the sum of the first ten natural numbers is,
    (1 + 2 + ... + 10)^2 = 552 = 3025
    Hence the difference between the sum of the squares of the first ten natural numbers and the square of the sum is 3025 - 385 = 2640.
    
    Find the difference between the sum of the squares of the first one hundred natural numbers and the square of the sum.
    '''

    r = xrange(1, max + 1)
    a = sum(r)
    return a * a - sum(i*i for i in r)
