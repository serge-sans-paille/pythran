#from loic gouarin
#pythran export  one_time_step(float64 [][][], float64 [][][])
#runas import numpy as np ; r = np.ones((50,50,9)); one_time_step(r,r)
#bench import numpy as np ; r = np.ones((500,500,9)); one_time_step(r,r)

import numpy as np

def m2f_loc(m, f):
    c0 = 1./6
    c1 = 1./9
    c2 = 1./18
    c3 = 1./36
    c4 = 1./12

    f[0] = c1*m[0] - c1*m[3] + c1*m[4]
    f[1] = c1*m[0] + c0*m[1] - c3*m[3] - c2*m[4] - c0*m[5] + 0.25*m[7]
    f[2] = c1*m[0] + c0*m[2] - c3*m[3] - c2*m[4] - c0*m[6] - 0.25*m[7]
    f[3] = c1*m[0] - c0*m[1] - c3*m[3] - c2*m[4] + c0*m[5] + 0.25*m[7]
    f[4] = c1*m[0] - c0*m[2] - c3*m[3] - c2*m[4] + c0*m[6] - 0.25*m[7]
    f[5] = c1*m[0] + c0*m[1] + c0*m[2] + c2*m[3] + c3*m[4] + c4*m[5] + c4*m[6] + 0.25*m[8]
    f[6] = c1*m[0] - c0*m[1] + c0*m[2] + c2*m[3] + c3*m[4] - c4*m[5] + c4*m[6] - 0.25*m[8]
    f[7] = c1*m[0] - c0*m[1] - c0*m[2] + c2*m[3] + c3*m[4] - c4*m[5] - c4*m[6] + 0.25*m[8]
    f[8] = c1*m[0] + c0*m[1] - c0*m[2] + c2*m[3] + c3*m[4] + c4*m[5] - c4*m[6] - 0.25*m[8]

def f2m_loc(f, m):
    m[0] = f[0] + f[1] + f[2] + f[3] + f[4] + f[5] + f[6] + f[7] + f[8]
    m[1] = f[1] - f[3] + f[5] - f[6] - f[7] + f[8]
    m[2] = f[2] - f[4] + f[5] + f[6] - f[7] - f[8]
    m[3] = -4.*f[0] - f[1] - f[2] - f[3] - f[4] + 2.*f[5] + 2.*f[6] + 2.*f[7] + 2.*f[8]
    m[4] = 4.*f[0] - 2.*f[1] - 2.*f[2] - 2.*f[3] - 2.*f[4] + f[5] + f[6] + f[7] + f[8]
    m[5] = -2.*f[1] + 2.*f[3] + f[5] - f[6] - f[7] + f[8]
    m[6] = -2.*f[2] + 2.*f[4] + f[5] + f[6] - f[7] - f[8]
    m[7] = f[1] - f[2] + f[3] - f[4]
    m[8] = f[5] - f[6] + f[7] - f[8]

def getf(f, floc, i, j):
    floc[0] = f[i, j, 0]
    floc[1] = f[i-1, j, 1]
    floc[2] = f[i, j-1, 2]
    floc[3] = f[i+1, j, 3]
    floc[4] = f[i, j+1, 4]
    floc[5] = f[i-1, j-1, 5]
    floc[6] = f[i+1, j-1, 6]
    floc[7] = f[i+1, j+1, 7]
    floc[8] = f[i-1, j+1, 8]

def setf(f, floc, i, j):
    f[j, i, 0] = floc[0]
    f[j, i, 1] = floc[1]
    f[j, i, 2] = floc[2]
    f[j, i, 3] = floc[3]
    f[j, i, 4] = floc[4]
    f[j, i, 5] = floc[5]
    f[j, i, 6] = floc[6]
    f[j, i, 7] = floc[7]
    f[j, i, 8] = floc[8]

def relaxation_loc(m):
    m[3] += 1.1312217194570136*(-2*m[0] + 3.0*m[1]*m[1] + 3.0*m[2]*m[2] - m[3])
    m[4] += 1.1312217194570136*(m[0] + 1.5*m[1]*m[1] + 1.5*m[2]*m[2] - m[4])
    m[5] += 1.1312217194570136*(-m[1] - m[5])
    m[6] += 1.1312217194570136*(-m[2] - m[6])
    m[7] += 1.8573551263001487*(m[1]*m[1] - m[2]*m[2] - m[7])
    m[8] += 1.8573551263001487*(m[1]*m[2] - m[8])

def periodic_bc(f):
    nx, ny, ns = f.shape

    for j in xrange(ny):
        for k in xrange(ns):
            f[0, j, k] = f[nx-2, j, k]
            f[nx-1, j, k] = f[1, j, k]
    for i in xrange(nx):
        for k in xrange(ns):
            f[i, 0, k] = f[i, ny-2, k]
            f[i, ny-1, k] = f[i, 1, k]

def one_time_step(f1, f2):
    nx, ny, ns = f1.shape
    floc = np.zeros(ns)
    mloc = np.zeros(ns)

    periodic_bc(f1)
    for i in range(1, nx-1):
        for j in range(1, ny-1):
            getf(f1, floc, i, j)
            f2m_loc(floc, mloc)
            relaxation_loc(mloc)
            m2f_loc(mloc, floc)
            setf(f2, floc, i, j)
    return f2

