#pythran export solve(int)
#runas solve(3)
def solve(digit):
    '''
    A palindromic number reads the same both ways. The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 x 99.
    
    Find the largest palindrome made from the product of two 3-digit numbers.
    '''

    n = 0
    for a in xrange(10 ** digit - 1, 10 ** (digit - 1), -1):
        for b in xrange(a, 10 ** (digit - 1), -1):
            x = a * b
            if x > n:
                s = str(a * b)
                if s == s[::-1]:
                    n = a * b

    return n
