#runas solve(1000)
#pythran export solve(int)
'''
Euler published the remarkable quadratic formula:

n^2 + n + 41

It turns out that the formula will produce 40 primes for the consecutive values n = 0 to 39. However, when n = 40, 402 + 40 + 41 = 40(40 + 1) + 41 is divisible by 41, and certainly when n = 41, 41^2 + 41 + 41 is clearly divisible by 41.

Using computers, the incredible formula  n^2 - 79n + 1601 was discovered, which produces 80 primes for the consecutive values n = 0 to 79. The product of the coefficients, -79 and 1601, is -126479.

Considering quadratics of the form:

n^2 + an + b, where |a| <= 1000 and |b| <= 1000

where |n| is the modulus/absolute value of n
e.g. |11| = 11 and |4| = 4
Find the product of the coefficients, a and b, for the quadratic expression that produces the maximum number of primes for consecutive values of n, starting with n = 0.

'''

def solve(edge):
 prime_list = [2, 3, 5, 7, 11, 13, 17, 19, 23]   # Ensure that this is initialised with at least 1 prime
 prime_dict = dict.fromkeys(prime_list, 1)

 def _isprime(n):
     ''' Raw check to see if n is prime. Assumes that prime_list is already populated '''
     isprime = n >= 2 and 1 or 0
     for prime in prime_list:                    # Check for factors with all primes
         if prime * prime > n: break             # ... up to sqrt(n)
         if not n % prime:
             isprime = 0
             break
     if isprime: prime_dict[n] = 1               # Maintain a dictionary for fast lookup
     return isprime

 def _refresh(x):
     ''' Refreshes primes upto x '''
     lastn = prime_list[-1]
     while lastn <= x:                           # Keep working until we've got up to x
         lastn = lastn + 1                       # Check the next number
         if _isprime(lastn):
             prime_list.append(lastn)            # Maintain a list for sequential access

 def prime(x):
     ''' Returns the xth prime '''

     lastn = prime_list[-1]
     while len(prime_list) <= x:                 # Keep working until we've got the xth prime
         lastn = lastn + 1                       # Check the next number
         if _isprime(lastn):
             prime_list.append(lastn)            # Maintain a list for sequential access
     return prime_list[x]

 max_pair = (0,0,0)
 for a in xrange(-1 * edge + 1, edge):
     for b in xrange(max(2, 1-a), edge): # b >= 2, a + b + 1 >= 2
         n, count = 0, 0
         while True:
             v = n*n + a*n + b
             _refresh(v)
             if _isprime(v): count = count + 1
             else: break
             n = n + 1
         if count > max_pair[2]:
             max_pair = (a,b,count)

 return max_pair[0] * max_pair[1]
