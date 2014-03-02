'''
Starting in the top left corner of a 2x2 grid, there are 6 routes (without backtracking) to the bottom right corner.

How many routes are there through a 20x20 grid?
'''

def fact(n):
    f = 1
    for x in xrange(1, n+1): f = f * x
    return f

print fact(40) / fact(20) / fact(20)
