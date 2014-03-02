#unittest.skip import prime
'''
The number 3797 has an interesting property. Being prime itself, it is possible to continuously remove digits from left to right, and remain prime at each stage: 3797, 797, 97, and 7. Similarly we can work from right to left: 3797, 379, 37, and 3.

Find the sum of the only eleven primes that are both truncatable from left to right and right to left.

NOTE: 2, 3, 5, and 7 are not considered to be truncatable primes.
'''

import math, prime

digits = range(0, 10)
prime_digits = (2, 3, 5, 7)

def num(l):
    s = 0
    for n in l: s = s * 10 + n
    return s

def is_left_truncatable(l):
    is_truncatable = 1
    for size in xrange(1, len(l)+1):
        n = num(l[:size])
        prime._refresh(int(math.sqrt(n)))
        if not prime._isprime(n):
            is_truncatable = 0
            break
    return is_truncatable

def is_right_truncatable(l):
    is_truncatable = 1
    for size in xrange(0, len(l)):
        n = num(l[size:])
        prime._refresh(int(math.sqrt(n)))
        if not prime._isprime(n):
            is_truncatable = 0
            break
    return is_truncatable

def gen(result, number):
    if len(number) > 6: return
    number = list(number)
    number.append('')
    for digit in digits:
        number[-1] = digit
        if is_left_truncatable(number):
            if is_right_truncatable(number) and len(number) > 1:
                result.append(num(number))
            gen(result, number)

result = []
gen(result, [])
print sum(result)
