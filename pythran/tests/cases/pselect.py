#pythran export pselect(int)
#runas pselect(0)
#runas pselect(1)
def pselect(n):
    l=list()
    for k in (n, not n):
        if k:
            a=sel0
        else:
            a=sel1
        a(l)
    return l

def sel0(n):
    n.append(1)
def sel1(n):
    n.append(2.)
