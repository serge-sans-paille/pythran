#runas solve()
#unittest.skip recursive generator
#pythran export solve()
''' From O'Reilly's Python Cookbook '''

def _combinators(_handle, items, n):
    if n==0:
        yield []
        return
    for i, item in enumerate(items):
        this_one = [ item ]
        for cc in _combinators(_handle, _handle(items, i), n-1):
            yield this_one + cc

def combinations(items, n):
    ''' take n distinct items, order matters '''
    def skipIthItem(items, i):
        return items[:i] + items[i+1:]
    return _combinators(skipIthItem, items, n)

def uniqueCombinations(items, n):
    ''' take n distinct items, order is irrelevant '''
    def afterIthItem(items, i):
        return items[i+1:]
    return _combinators(afterIthItem, items, n)

def selections(items, n):
    ''' take n (not necessarily distinct) items, order matters '''
    def keepAllItems(items, i):
        return items
    return _combinators(keepAllItems, items, n)

def permutations(items):
    ''' take all items, order matters '''
    return combinations(items, len(items))
def solve():
    '''
    We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n exactly once. For example, 2143 is a 4-digit pandigital and is also prime.
    
    What is the largest n-digit pandigital prime that exists?
    '''

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



    # Pan-digital primes are 4 or 7 digits. Others divisible by 3
    _refresh(2766)    # sqrt(7654321)
    for perm in permutations(range(7, 0, -1)):
        num = 0
        for n in perm: num = num * 10 + n
        if _isprime(num):
            return num
            break

