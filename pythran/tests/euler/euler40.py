#runas solve()
#pythran export solve()
def solve():
    '''
    An irrational decimal fraction is created by concatenating the positive integers:
    
    0.123456789101112131415161718192021...
    
    It can be seen that the 12th digit of the fractional part is 1.
    
    If dn represents the nth digit of the fractional part, find the value of the following expression.
    
    d1 x d10 x d100 x d1000 x d10000 x d100000 x d1000000
    
    0 digit < 1
    1 digit < + 9 * 1           10
    2 digit < + 90 * 2          190
    3 digit < + 900 * 3         2890
    4 digit < + 9000 * 4
    5 digit < + 90000 * 5
    '''

    def digit_at(n):
        digits = 1
        n = n - 1
        while True:
            numbers = 9 * pow(10L, digits-1) * digits
            if n > numbers: n = n - numbers
            else: break
            digits = digits + 1
        num = n / digits + pow(10L, digits-1)
        return int(str(num)[n % digits])

    return digit_at(1) * digit_at(10) * digit_at(100) * digit_at(1000) * digit_at(10000) * digit_at(100000) * digit_at(1000000)

