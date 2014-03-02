'''
Find the sum of digits in 100!
'''

def digits(n):
    s = 0
    while n > 0:
        s = s + (n % 10)
        n = n / 10
    return s

n = 1
for i in xrange(1,100): n = n*i
print digits(n)
