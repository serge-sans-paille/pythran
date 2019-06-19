#runas import numpy as np; x = np.arange(5.); y = np.arange(5.); z = np.arange(5.); resample(x,y,z)
#pythran export resample(float[], float[], float[])
import numpy as np
def resample(qs, xs, rands):
    lookup = np.cumsum(qs)
    mm = lookup[None,:]>rands[:,None]
    I = np.argmax(mm,1)
    return xs[I]
