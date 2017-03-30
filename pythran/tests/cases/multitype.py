#pythran export square(int or float)
#runas square(200)
#runas square(200.200)

def square(n):
    return n*n

#pythran export mul([int or float] list, int)
#runas mul([1], 2)
#runas mul([1.5], 2)

#pythran export mul(int or float list, int or bool)
#runas mul(1, 2)
#runas mul([1.5], 2)
#runas mul(1, True)
#runas mul([1.5], False)

def mul(x, y):
    return x * y
