#runas solve(10000)
#pythran export solve(int)
'''
 Let d(n) be defined as the sum of proper divisors of n (numbers less than n which divide evenly into n).
 If d(a) = b and d(b) = a, where a  b, then a and b are an amicable pair and each of a and b are called amicable numbers.

 For example, the proper divisors of 220 are 1, 2, 4, 5, 10, 11, 20, 22, 44, 55 and 110; therefore d(220) = 284. The proper divisors of 284 are 1, 2, 4, 71 and 142; so d(284) = 220.

 Evaluate the sum of all the amicable numbers under 10000.
'''

def divisors(n): return list(i for i in xrange(1, n/2+1) if n % i == 0)
def solve(m):
	pair = dict( ((n, sum(divisors(n))) for n in xrange(1, m)) )
	return sum(n for n in xrange(1, m) if pair.get(pair[n], 0) == n and pair[n] != n)
