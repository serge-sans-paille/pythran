import numpy as np

def perm(data, p):
    n = len(data)
    out = np.empty(n)
    #pragma omp simd
    for i in range(n):
        out[i] = data[p[i]] * 2
    return out

def simd():
    data = [10, 20, 30, 40]
    p = [1, 0, 3, 2]
    res = perm(data, p)
    return np.all(res == [40, 20, 80, 60])
