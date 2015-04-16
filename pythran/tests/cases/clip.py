#pythran export clip(complex128[], float64)
#pythran export clip(complex128[::], float64)
#runas import numpy as np ; a = np.arange(2, dtype=complex); clip(a, .5), clip(a[2::4], .5)

import numpy as np

def limit1 (x, epsilon=1e-6):
    if abs(x) < epsilon:
        return 0
    else:
        return x / abs(x)

def clip (z, _max):
    out = np.empty (z.shape, dtype=z.dtype)
    for i in range (len(z)):
        if abs(z[i]) > _max:
            out[i] = limit1 (z[i]) * _max
        else:
            out[i] = z[i]

    return out
