'''
Find the value of d < 1000 for which 1 / d contains the longest recurring cycle
'''

def cycle_length(n):
    i = 1
    if n % 2 == 0: return cycle_length(n / 2)
    if n % 5 == 0: return cycle_length(n / 5)
    while True:
        if (pow(10, i) - 1) % n == 0: return i
        else: i = i + 1

m = 0
n = 0
for d in xrange(1,1000):
    c = cycle_length(d)
    if c > m:
        m = c
        n = d

print n
