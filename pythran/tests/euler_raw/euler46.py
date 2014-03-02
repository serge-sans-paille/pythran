'''
It was proposed by Christian Goldbach that every odd composite number can be written as the sum of a prime and twice a square.

 9 =  7 + 2 x 1^2
15 =  7 + 2 x 2^2
21 =  3 + 2 x 3^2
25 =  7 + 2 x 3^2
27 = 19 + 2 x 2^2
33 = 31 + 2 x 1^2
It turns out that the conjecture was false.

What is the smallest odd composite that cannot be written as the sum of a prime and twice a square?
'''

import prime
MAX = 10000
squares = dict.fromkeys((x*x for x in xrange(1, MAX)), 1)
prime._refresh(MAX)

for x in xrange(35, MAX, 2):
    if not prime.isprime(x):
        is_goldbach = 0
        for p in prime.prime_list[1:]:
            if p >= x: break
            if squares.has_key((x - p)/2):
                is_goldbach = 1
                break
        if not is_goldbach:
            print x
            break
