#pythran export pselect(int)
def pselect(n):
    if n:
        a=sel0
    else:
        a=sel1
    l=list()
    a(l)
    print l

def sel0(n):
    n.append(1)
def sel1(n):
    n.append(1.)
