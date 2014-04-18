#from http://stackoverflow.com/questions/7741878/how-to-apply-numpy-linalg-norm-to-each-row-of-a-matrix/7741976#7741976
#pythran export l2_norm(float64[][])
#runas import numpy as np ; N = 100 ; x = np.arange(N*N, dtype=np.float64).reshape((N,N)) ; l2_norm(x)
#bench import numpy as np ; N = 10000 ; x = np.arange(N*N, dtype=np.float64).reshape((N,N)) ; l2_norm(x)
import numpy as np
def l2_norm(x):
    return np.sqrt(np.sum(np.abs(x)**2, 1))
