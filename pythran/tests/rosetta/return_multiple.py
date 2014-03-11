#from http://rosettacode.org/wiki/Return_multiple_values
#pythran export addsub(int, int)
#runas addsub(33, 12)

def addsub(x, y):
    return x + y, x - y
