import numpy as np

#runas import numpy as np; r = np.arange(1000000, dtype=float); rosen(r)
#bench import numpy as np; r = np.arange(50000000); rosen(r)
#pythran export rosen(int[])
#pythran export rosen(float[])

def rosen(x):
    t0 = 100 * (x[1:] - x[:-1] ** 2) ** 2
    t1 = (1 - x[:-1]) ** 2
    return np.sum(t0 + t1)
