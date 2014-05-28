#from: http://stackoverflow.com/questions/20799403/improving-performance-of-cronbach-alpha-code-python-numpy
#pythran export cronbach(float [][])
#runas import numpy as np ; N = 800 ; items = np.arange(N*N, dtype=float).reshape(N,N) ; cronbach(items)
#bench import numpy as np ; N = 800 ; items = np.arange(N*N, dtype=float).reshape(N,N) ; cronbach(items)
def cronbach(itemscores):
    itemvars = itemscores.var(1, None, None, 1)#(axis=1, ddof=1)
    tscores = itemscores.sum(0)#(axis=0)
    nitems = len(itemscores)
    return nitems / (nitems-1) * (1 - itemvars.sum() / tscores.var(None, None, None, 1))#(ddof=1))
