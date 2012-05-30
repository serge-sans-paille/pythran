#pythran export select(int)
def select(n):
    if n:
        a=sel0
    else:
        a=sel1
    a(3)

def sel0(n):
    print "0"
def sel1(n):
    print "1"
