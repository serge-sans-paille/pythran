#from http://rosettacode.org/wiki/Pascal%27s_triangle#Python
#pythran export pascal(int)
#pythran export pascal_(int)
#runas pascal(10)
#runas pascal_(10)

def pascal(n):
    """Prints out n rows of Pascal's triangle.
    It returns False for failure and True for success."""
    row = [1]
    k = [0]
    for x in range(max(n,0)):
        print row
        row=[l+r for l,r in zip(row+k,k+row)]
    return n>=1

def scan(op, seq, it):
    a = []
    result = it
    a.append(it)
    for x in seq:
        result = op(result, x)
        a.append(result)
    return a

def pascal_(n):
    def nextrow(row, x):
        return [l+r for l,r in zip(row+[0,],[0,]+row)]
    return scan(nextrow, range(n-1), [1,])
