#runas solve(2)
#pythran export solve(int)
def solve(digit):
    '''
    The fraction 49/98 is a curious fraction, as an inexperienced mathematician in attempting to simplify it may incorrectly believe that 49/98 = 4/8, which is correct, is obtained by cancelling the 9s.

    We shall consider fractions like, 30/50 = 3/5, to be trivial examples.

    There are exactly four non-trivial examples of this type of fraction, less than one in value, and containing two digits in the numerator and denominator.

    If the product of these four fractions is given in its lowest common terms, find the value of the denominator.
    '''

    def fractions():
        for numerator in map(str, xrange(10 ** (digit - 1), 10 ** digit)):
            for denominator in map(str, xrange(int(numerator)+1, 10 ** digit)):
                if numerator == denominator: continue
                if numerator[1] == denominator[1] and numerator[1] == '0': continue
                if numerator[0] == denominator[0] and int(numerator) * int(denominator[1]) == int(denominator) * int(numerator[1]): yield(int(numerator), int(denominator))
                if numerator[0] == denominator[1] and int(numerator) * int(denominator[0]) == int(denominator) * int(numerator[1]): yield(int(numerator), int(denominator))
                if numerator[1] == denominator[1] and int(numerator) * int(denominator[0]) == int(denominator) * int(numerator[0]): yield(int(numerator), int(denominator))
                if numerator[1] == denominator[0] and int(numerator) * int(denominator[1]) == int(denominator) * int(numerator[0]): yield(int(numerator), int(denominator))

    def gcd(a,b): return b and gcd(b, a % b) or a

    numerator = 1
    denominator = 1
    for frac in fractions():
        numerator = numerator * frac[0]
        denominator = denominator * frac[1]

    g = gcd(numerator, denominator)
    return denominator / g

