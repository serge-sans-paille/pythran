#from: http://stackoverflow.com/questions/16541618/perform-a-reverse-cumulative-sum-on-a-numpy-array
#pythran export reverse_cumsum(float[])
#runas import numpy as np ; r = np.arange(10, dtype=float) ; reverse_cumsum(r)
#bench import numpy as np ; r = np.arange(1000000, dtype=float) ; reverse_cumsum(r)
import numpy as np
def reverse_cumsum(x):
    return np.cumsum(x[::-1])[::-1]
