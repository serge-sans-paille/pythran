#runas solve()
#pythran export solve()
def solve():
    '''
    The decimal number, 585 = 10010010012 (binary), is palindromic in both bases.
    
    Find the sum of all numbers, less than one million, which are palindromic in base 10 and base 2.
    
    (Please note that the palindromic number, in either base, may not include leading zeros.)
    '''

    def ispalindrome(n, base):
        digits = []
        reverse = []
        while n > 0:
            d = str(n % base)
            digits.append(d)
            reverse.insert(0, d)
            n = n / base
        return digits == reverse

    return sum(n for n in xrange(1, 1000000) if ispalindrome(n, 10) and ispalindrome(n, 2))

