#from http://rosettacode.org/wiki/Zeckendorf_number_representation#Python
#pythran export test(int)
#pythran export z(int)
#pythran export zeckendorf(int)
#runas test(20)
#runas ['%3i: %8s' % (i, ''.join(str(d) for d in zeckendorf(i))) for i in range(21)]
#runas ['%3i: %8s' % (i, ''.join(str(d) for d in z(i))) for i in range(21)]

def fib():
    memo = [1, 2]
    while True:
        memo.append(sum(memo))
        yield memo.pop(0)

def sequence_down_from_n(n, seq_generator):
    seq = []
    for s in seq_generator():
        seq.append(s)
        if s >= n: break
    return seq[::-1]

def zeckendorf(n):
    if n == 0: return [0]
    seq = sequence_down_from_n(n, fib)
    digits, nleft = [], n
    for s in seq:
        if s <= nleft:
            digits.append(1)
            nleft -= s
        else:
            digits.append(0)
    assert nleft == 0, 'Check all of n is accounted for'
    assert sum(x*y for x,y in zip(digits, seq)) == n, 'Assert digits are correct'
    while digits[0] == 0:
        # Remove any zeroes padding L.H.S.
        digits.pop(0)
    return digits

def z(n):
    if n == 0 : return [0]
    fib = [2,1]
    while fib[0] < n: fib[0:0] = [sum(fib[:2])]
    dig = []
    for f in fib:
        if f <= n:
            dig, n = dig + [1], n - f
        else:
            dig += [0]
    return dig if dig[0] else dig[1:]

def test(n):
    return sequence_down_from_n(n, fib)

