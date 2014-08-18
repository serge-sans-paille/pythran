#pythran export map0(float [])
def map0(r):
    l = vmap(lambda x: 5*x + 3, r)
    return l[len(l)/2]
