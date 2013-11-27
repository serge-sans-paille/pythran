#pythran export map0(int)
def map0(n):
    r = range(n)
    l = vmap(lambda x: 5*x + 3, r)
    return l[len(l)/2]
