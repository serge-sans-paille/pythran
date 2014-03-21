#runas solve(10001)
#pythran export solve(int)
'''
Starting with the number 1 and moving to the right in a clockwise direction a 5 by 5 spiral is formed as follows:
43                49
    21 22 23 24 25
    20  7  8  9 10
    19  6  1  2 11
    18  5  4  3 12
    17 16 15 14 13
37                31
                    57
1
6*4
19*4
39*4
69*4

It can be verified that the sum of both diagonals is 101.

What is the sum of both diagonals in a 1001 by 1001 spiral formed in the same way?
'''

def solve(size):
 diagonal = 1L
 start = 1
 for width in xrange(3, size + 1, 2):
     increment = width - 1
     count = increment * 4
     diagonal = diagonal + start * 4 + increment * 10
     start = start + count

 return diagonal
