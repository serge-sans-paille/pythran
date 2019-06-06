#from: https://stackoverflow.com/questions/55854611/efficient-way-of-vectorizing-distance-calculation/55877642#55877642
#pythran export l1norm(float64[][], float64[:,:])
#runas import numpy as np ; N = 100 ; x = np.arange(N*N, dtype=np.float64).reshape((N,N)); y = np.arange(N*N, dtype=np.float64).reshape((N,N)) ; l1norm(x, y)
import numpy as np
def l1norm(x, y):
    return np.sum(np.abs(x[:, None, :] - y), axis=-1)
