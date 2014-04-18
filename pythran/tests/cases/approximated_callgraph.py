#pythran export approximated_callgraph(int)
#runas approximated_callgraph(1000)
#bench approximated_callgraph(2500)
def call(i, j):
    return i+j

def approximated_callgraph(size):
    out= list()
    for i in xrange(size):
        out.append(map(lambda j:call(i, j), xrange(size)))
    return out
