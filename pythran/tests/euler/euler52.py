#runas solve()
#pythran export solve()
def solve():
    '''
    It can be seen that the number, 125874, and its double, 251748, contain exactly the same digits, but in a different order.
    
    Find the smallest positive integer, x, such that 2x, 3x, 4x, 5x, and 6x, contain the same digits.
    '''

    def multiples_have_same_digits(n):
        digit_keys = dict.fromkeys(list(str(n)))
        for x in range(2, 4):
            for d in list(str(x * n)):
                if d not in digit_keys: return False
        return True

    n = 0
    while True:
        n = n + 9                           # n must be a multiple of 9 for this to happen
        if multiples_have_same_digits(n):
            return n
            break

