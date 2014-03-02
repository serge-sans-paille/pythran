#unittest.skip import prime
'''
A perfect number is a number for which the sum of its proper divisors is exactly equal to the number. For example, the sum of the proper divisors of 28 would be 1 + 2 + 4 + 7 + 14 = 28, which means that 28 is a perfect number.

A number whose proper divisors are less than the number is called deficient and a number whose proper divisors exceed the number is called abundant.

As 12 is the smallest abundant number, 1 + 2 + 3 + 4 + 6 = 16, the smallest number that can be written as the sum of two abundant numbers is 24. By mathematical analysis, it can be shown that all integers greater than 28123 can be written as the sum of two abundant numbers. However, this upper limit cannot be reduced any further by analysis even though it is known that the greatest number that cannot be expressed as the sum of two abundant numbers is less than this limit.

Find the sum of all the positive integers which cannot be written as the sum of two abundant numbers.
'''

import prime

MAX = 28124
prime._refresh(MAX/2)
abundants = [n for n in xrange(1, MAX) if sum(prime.all_factors(n)) > n+n]
abundants_dict = dict.fromkeys(abundants, 1)

total = 0
for n in xrange(1, MAX):
    sum_of_abundants = 0
    for a in abundants:
        if a > n: break
        if abundants_dict.get(n - a):
            sum_of_abundants = 1
            break
    if not sum_of_abundants:
        total = total + n

print total
