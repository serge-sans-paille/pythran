import numpy as np
cimport numpy as np
cimport cython

DTYPE = np.double
ctypedef np.double_t DTYPE_t
@cython.boundscheck(False)
def wave(double t, double t_stop, double dt, double dx, double dy, np.ndarray[DTYPE_t, ndim=2, negative_indices=False] u, np.ndarray[DTYPE_t, ndim=2, negative_indices=False] um, np.ndarray[DTYPE_t, ndim=2, negative_indices=False] k):
    cdef np.ndarray[DTYPE_t, ndim=2, negative_indices=False] new_u
    while t <= t_stop:
        t += dt
        new_u = calculate_u(dt, dx, dy, u, um, k)
        um = u
        u = new_u
    return u

@cython.boundscheck(False)
def calculate_u(double dt, double dx, double dy, np.ndarray[DTYPE_t, ndim=2, negative_indices=False] u, np.ndarray[DTYPE_t, ndim=2, negative_indices=False] um, np.ndarray[DTYPE_t, ndim=2, negative_indices=False] k):
    cdef np.ndarray[DTYPE_t, ndim=2, negative_indices=False] up = np.zeros((u.shape[0], u.shape[1]))
    cdef int i,j
    "omp parallel for private(i,j)"
    for i in xrange(1, u.shape[0]-1):
        for j in xrange(1, u.shape[1]-1):
            up[i,j] = 2*u[i,j] - um[i,j] + \
                (dt/dx)**2*(
                        (0.5*(k[i+1,j] + k[i,j])*(u[i+1,j] - u[i,j]) -
                            0.5*(k[i,j] + k[i-1,j])*(u[i,j] - u[i-1,j]))) + \
                        (dt/dy)**2*(
                                (0.5*(k[i,j+1] + k[i,j])*(u[i,j+1] - u[i,j]) -
                                    0.5*(k[i,j] + k[i,j-1])*(u[i,j] - u[i,j-1])))
    return up

