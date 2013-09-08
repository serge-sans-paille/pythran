#runas solve()
#pythran export solve()
def solve():
    '''
    A palindromic number reads the same both ways. The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 x 99.
    
    Find the largest palindrome made from the product of two 3-digit numbers.
    '''
    
    n = 0
    for a in xrange(999, 100, -1):
        for b in xrange(a, 100, -1):
            x = a * b
            if x > n:
                s = str(a * b)
                if s == s[::-1]:
                    n = a * b
    
    return n
