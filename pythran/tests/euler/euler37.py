#runas solve()
#pythran export solve()
def solve():
    '''
    The number 3797 has an interesting property. Being prime itself, it is possible to continuously remove digits from left to right, and remain prime at each stage: 3797, 797, 97, and 7. Similarly we can work from right to left: 3797, 379, 37, and 3.
    
    Find the sum of the only eleven primes that are both truncatable from left to right and right to left.
    
    NOTE: 2, 3, 5, and 7 are not considered to be truncatable primes.
    '''

    import math

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

    digits = range(0, 10)
    prime_digits = (2, 3, 5, 7)


    def num(l):
        s = 0
        for n in l: s = s * 10 + n
        return s

    def is_left_truncatable(l):
        is_truncatable = 1
        for size in xrange(1, len(l)+1):
            n = num(l[:size])
            _refresh(int(math.sqrt(n)))
            if not _isprime(n):
                is_truncatable = 0
                break
        return is_truncatable

    def is_right_truncatable(l):
        is_truncatable = 1
        for size in xrange(0, len(l)):
            n = num(l[size:])
            _refresh(int(math.sqrt(n)))
            if not _isprime(n):
                is_truncatable = 0
                break
        return is_truncatable

    def gen(result, number):
        if len(number) > 6: return
        number = list(number)
        number.append(0)
        for digit in digits:
            number[-1] = digit
            if is_left_truncatable(number):
                if is_right_truncatable(number) and len(number) > 1:
                    result.append(num(number))
                gen(result, number)

    result = []
    gen(result, [])
    return sum(result)

