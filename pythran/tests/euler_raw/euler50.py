'''
The prime 41, can be written as the sum of six consecutive primes:

41 = 2 + 3 + 5 + 7 + 11 + 13
This is the longest sum of consecutive primes that adds to a prime below one-hundred.

The longest sum of consecutive primes below one-thousand that adds to a prime, contains 21 terms, and is equal to 953.

Which prime, below one-million, can be written as the sum of the most consecutive primes?
'''
import prime

MAX = 5000
prime.prime(MAX)

def check_length(n, below):
    maxprime = 0
    for x in xrange(0, below):
        total = sum(prime.prime_list[x:x+n])
        if total > below: break
        if prime.isprime(total): maxprime = total
    return maxprime

for n in xrange(1000, 0, -1):
    maxprime = check_length(n, 1000000)
    if maxprime:
        print maxprime
        break
