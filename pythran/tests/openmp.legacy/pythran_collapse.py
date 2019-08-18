import numpy as np
def collapse_bug(x, m, btx):
    n = int(np.log2(m))
    lv = np.zeros((x.shape[0], n))
    N = x.shape[0]
    #omp parallel for collapse(2)
    for i in range(N):
        for k in range(n):
            lv[i,k] = abs(x[i]- btx[k])
    return lv

def pythran_collapse():
    from random import randint
    n = randint(50, 50)
    x = np.ones(n)
    return collapse_bug(x, 5, 3. * x)
