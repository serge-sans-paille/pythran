#runas solve(5)
#pythran export solve(int)

'''
Surprisingly there are only three numbers that can be written as the sum of fourth powers of their digits:

1634 = 1^4 + 6^4 + 3^4 + 4^4
8208 = 8^4 + 2^4 + 0^4 + 8^4
9474 = 9^4 + 4^4 + 7^4 + 4^4
As 1 = 1^4 is not a sum it is not included.

The sum of these numbers is 1634 + 8208 + 9474 = 19316.

Find the sum of all the numbers that can be written as the sum of fifth powers of their digits.
'''

def power_of_digits(n, p):
    s = 0
    while n > 0:
        d = n % 10
        n = n / 10
        s = s + pow(d, p)
    return s


def solve(p):
 return sum(n for n in xrange(2, 200000) if power_of_digits(n, p) == n)

