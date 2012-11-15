#pythran export solve()
def solve():
    '''
    Find the first four consecutive integers to have four distinct prime factors
    '''
    
    import prime
    
    def distinct_factors(n): return len(dict.fromkeys(prime.factors(n)).keys())
    
    factors = [0, 1, distinct_factors(2), distinct_factors(3)]
    while True:
        if factors[-4::] == [4,4,4,4]: break
        else: factors.append(distinct_factors(len(factors)))
    
    print len(factors)-4
