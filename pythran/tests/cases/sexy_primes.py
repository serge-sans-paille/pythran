#from http://stackoverflow.com/questions/11641098/interpreting-a-benchmark-in-c-clojure-python-ruby-scala-and-others
#runas primes_below(10*1000)
#pythran export primes_below(int)
def is_prime(n):
      return all((n%j > 0) for j in xrange(2, n))

def primes_below(x):
        return [[j-6, j] for j in xrange(9, x+1) if is_prime(j) and is_prime(j-6)]

