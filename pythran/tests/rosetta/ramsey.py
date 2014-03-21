#from http://rosettacode.org/wiki/Ramsey%27s_theorem#Python
#pythran export test()
#runas test()

def test():
    range17 =  range(17)
    a = [['0'] * 17 for i in range17]
    for i in range17:
        a[i][i] = '-'
    for k in range(4):
        for i in range17:
            j = (i + pow(2, k)) % 17
            a[i][j] = a[j][i] = '1'
    for row in a:
        print(' '.join(row))
