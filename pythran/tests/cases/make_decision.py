import numpy as np
#pythran export md(complex128[], complex128[])
#pythran export md(complex128[], complex128[::])
#runas import numpy as np;  s=np.arange(160.)+np.arange(160.)*1.j ; sc = s[::2]; md(s, sc)
def md(E, symbols):
    L = E.shape[0]
    M = symbols.shape[0]
    syms_out = np.zeros(L, dtype=E.dtype)
    #omp parallel for
    for i in range(L):
        im = np.argmin(abs(E[i]-symbols)**2)
        syms_out[i] = symbols[im]
    return syms_out
