#pythran export map1(int)
def map1(n):
    r = range(n)
    l = vmap(abs, r)
    return l[len(l)/2]
