#pythran export approximated_callgraph(int)
#runas approximated_callgraph(100)
#bench approximated_callgraph(250)
def call(i, j):
    return i+j

def approximated_callgraph(size):
    out= list()
    for i in range(size):
        out.append(list(map(lambda j:call(i, j), range(size))))
    return out
