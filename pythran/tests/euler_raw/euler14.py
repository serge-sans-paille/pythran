'''
The following iterative sequence is defined for the set of positive integers
n -> n/2 (n is even)
n -> 3n + 1 (n is odd)

Using the rule above and starting with 13, we generate the following sequence:
13 -> 40 -> 20 -> 10 -> 5 -> 16 -> 8 -> 4 -> 2 -> 1

It can be seen that this sequence (starting at 13 and fiinishing at 1) contains 10 terms.
Although it has not been proved yet (Collatz Problem), it is thought that all starting numbers finish at 1.

Which starting number, under one million, produces the longest chain?

NOTE: Once the chain starts the terms are allowed to go above one million.
'''

cache = { 1: 1 }
def chain(cache, n):
    if not cache.get(n,0):
        if n % 2: cache[n] = 1 + chain(cache, 3*n + 1)
        else: cache[n] = 1 + chain(cache, n/2)
    return cache[n]

m,n = 0,0
for i in xrange(1, 1000000):
    c = chain(cache, i)
    if c > m: m,n = c,i

print n
