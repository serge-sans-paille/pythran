# cython: np_pythran=True
cimport numpy as np
ctypedef np.double_t DTYPE_t

def add(np.ndarray[DTYPE_t, ndim=2] f, np.ndarray[DTYPE_t, ndim=2] g):
    return f + g
