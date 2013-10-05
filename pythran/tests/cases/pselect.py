#pythran export pselect(int)
#runas pselect(0)
#runas pselect(1)
def pselect(n):
    if n:
        a=sel0
    else:
        a=sel1
    l=list()
    a(l)
    return l

def sel0(n):
    n.append(1)
def sel1(n):
    n.append(2.)
