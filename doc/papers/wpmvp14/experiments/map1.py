#pythran export map1(float [])
def map1(r):
    l = vmap(abs, r)
    return l[len(l)/2]
