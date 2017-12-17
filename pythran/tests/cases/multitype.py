#pythran export times(int or str, int)
#runas times(200, 3)
#runas times('200', 3)

def times(n, m):
    return n*m

#pythran export check([str or float] list, int)
#runas check(['1'], 2)
#runas check([1.5], 2)

def check(x, y):
    if y:
        return x, y
    else:
        return x + x, y

#pythran export check2(str or float list, str or bool list)
#runas check2('1', '2')
#runas check2('1', [True])
#runas check2([1.5], 'True')
#runas check2([1.5], [False])

def check2(x, y):
    if y:
        return x, y
    else:
        return x + x, y
