# pythran export clip(complex128[], float64)
# pythran export limit (complex128[])
# runas import numpy as np ; a = np.arange(2, dtype=complex); clip(a, .5), clip(a[2::4], .5)

import numpy as np


def limit (x, epsilon=1e-6):
    out = np.empty(shape=x.shape, dtype=x.dtype)
    mask1 = np.abs(x) < epsilon
    out[mask1] = 0
    mask2 = np.logical_not(mask1)
    out[mask2] = x[mask2] / np.abs(x[mask2])
    return out

def clip (z, _max):
    mask = np.abs(z) > _max
    z[mask] = limit(z[mask]) * _max
    return z
