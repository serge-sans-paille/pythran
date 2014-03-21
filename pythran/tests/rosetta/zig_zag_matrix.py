#from http://rosettacode.org/wiki/Zig-zag_matrix#Python
#pythran export zigzag(int)
#pythran export czigzag(int)
#runas zigzag(5)
#runas czigzag(5)

def zigzag(n):
    def move(i, j):
        if j < (n - 1):
            return max(0, i-1), j+1
        else:
            return i+1, j
    a = [[0] * n for _ in xrange(n)]
    x, y = 0, 0
    for v in xrange(n * n):
        a[y][x] = v
        if (x + y) & 1:
            x, y = move(x, y)
        else:
            y, x = move(y, x)
    return a

def czigzag(COLS):
    def CX(x, ran):
      while True:
        x += 2 * next(ran)
        yield x
        x += 1
        yield x
    ran = []
    d = -1
    for V in CX(1,iter(list(range(0,COLS,2)) + list(range(COLS-1-COLS%2,0,-2)))):
      ran.append(iter(range(V, V+COLS*d, d)))
      d *= -1

    r=[]
    for x in range(0,COLS):
        t=[]
        for y in range(x, x+COLS):
            t.append(next(ran[y]))
        r.append(t)
    return r
