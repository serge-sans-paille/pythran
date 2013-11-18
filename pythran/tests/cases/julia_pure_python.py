# --- Python / Numpy imports -------------------------------------------------
import numpy as np
from time import time
#pythran export compute_julia(float, float, int, float, float, int)

def kernel(zr, zi, cr, ci, lim, cutoff):
    ''' Computes the number of iterations `n` such that 
        |z_n| > `lim`, where `z_n = z_{n-1}**2 + c`.
    '''
    count = 0
    while ((zr*zr + zi*zi) < (lim*lim)) and count < cutoff:
        zr, zi = zr * zr - zi * zi + cr, 2 * zr * zi + ci
        count += 1
    return count

def compute_julia(cr, ci, N, bound=1.5, lim=1000., cutoff=1e6):
    ''' Pure Python calculation of the Julia set for a given `c`.  No NumPy
        array operations are used.
    '''
    julia = np.empty((N, N), np.uint32)
    grid_x = np.linspace(-bound, bound, N)
    t0 = time()
    "omp parallel for private(i,x,j,y) default(none) shared(grid_x, cr, ci, lim, cutoff, julia)"
    for i, x in enumerate(grid_x):
        for j, y in enumerate(grid_x):
            julia[i,j] = kernel(x, y, cr, ci, lim, cutoff)
    return julia, time() - t0
