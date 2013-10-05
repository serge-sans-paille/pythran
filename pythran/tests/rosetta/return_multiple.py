#from http://rosettacode.org/wiki/Return_multiple_values

def addsub(x, y):
    return x + y, x - y

def test():
    sum, difference = addsub(33, 12)
    print "33 + 12 = %s" % sum
    print "33 - 12 = %s" % difference
