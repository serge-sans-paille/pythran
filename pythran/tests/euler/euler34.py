#runas solve()
#pythran export solve()
def solve():
    '''
    145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.
    
    Find the sum of all numbers which are equal to the sum of the factorial of their digits.
    
    Note: as 1! = 1 and 2! = 2 are not sums they are not included.
    '''

    fact = [1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880]

    def sum_of_digits_factorial(n):
        s = 0
        while n > 0:
            d = n % 10
            s = s + fact[d]
            n = n / 10
        return s

    return sum(n for n in xrange(10, 100000) if n == sum_of_digits_factorial(n))
