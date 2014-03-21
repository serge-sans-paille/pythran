#from http://rosettacode.org/wiki/Real_constants_and_functions#Python
#pythran export test()
#runas test()

def test():
    import math
    x = 3.5
    y = -0.2
    print math.e          # e
    print math.pi         # pi
    print math.sqrt(x)    # square root  (Also commonly seen as x ** 0.5 to obviate importing the math module)
    print math.log(x)     # natural logarithm
    print math.log10(x)   # base 10 logarithm
    print math.exp(x)     # e raised to the power of x
    print abs(x)          # absolute value
    print math.floor(x)   # floor
    print math.ceil(x)    # ceiling
    print x ** y          # exponentiation 
    print pow(x, y)
