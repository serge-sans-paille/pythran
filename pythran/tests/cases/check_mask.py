#pythran export check_mask(bool[][], bool[])
#runas import numpy as np; db = np.array([[0,1,1,0], [1,0,1,1], [1,1,1,1]], dtype=bool); out = np.zeros(3,dtype=bool); check_mask(db, out)
#from http://stackoverflow.com/questions/34500913/numba-slower-for-numpy-bitwise-and-on-boolean-arrays
import numpy as np
def check_mask(db, out, mask=[1, 0, 1]):
    for idx, line in enumerate(db):
        target, vector = line[0], line[1:]
        if (mask == np.bitwise_and(mask, vector)).all():
            if target == 1:
                out[idx] = 1
    return out

