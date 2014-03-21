#runas solve(1000)
#pythran export solve(int)
'''
What is the first term in the Fibonacci sequence to contain 1000 digits
'''

import math
def solve(digit):
 phi = (1 + pow(5, 0.5)) / 2
 c = math.log10(5) / 2
 logphi = math.log10(phi)
 n = 1
 while True:
     if n * logphi - c >= digit - 1:
         return n
         break
     n = n + 1
