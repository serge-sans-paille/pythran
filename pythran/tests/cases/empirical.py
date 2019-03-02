#from https://github.com/serge-sans-paille/pythran/issues/1229
#runas import numpy as np; x = np.arange(3., 10.); empirical(x, 3., .5)
import numpy as np

#pythran export empirical(float[:], float, float)
def empirical(ds, alpha, x):
    sds = np.sort(ds)
    ds_to_the_alpha = sds**alpha
    fractions = ds_to_the_alpha #/ sum (ds_to_the_alpha)
    thresholds = np.cumsum(fractions)
    thresholds /= thresholds[-1]
    i = find_first (thresholds, lambda u: x < u)
    return i

#pthran export find_first(float[:], bool (float))
def find_first (seq, pred):
    for i,x in enumerate (seq):
        print(i, x, pred(x))
        if pred(x):
            return i
    return None


