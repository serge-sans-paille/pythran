__all__ = ['add_pressure_diffusion', 'cross1', 'cross2']

#runas import numpy as np; x = np.empty((3,2,5,7)); y = np.arange(210.).reshape(3,2,5,7); z = np.arange(210.).reshape(3,2,5,7) + 3; cross1(x,y,z)
#runas import numpy as np; x = np.empty((3,2,5,7), dtype=complex); y = np.arange(210.).reshape(3,2,5,7); z = np.arange(210., dtype=complex).reshape(3,2,5,7) + 3; cross2(x,y,z)
#runas import numpy as np; x = np.empty((3,2,5,7), dtype=complex); y = np.arange(210, dtype=np.int64).reshape(3,2,5,7); z = np.arange(210., dtype=complex).reshape(3,2,5,7) + 3; cross2(x,y,z)
#runas import numpy as np; x = np.ones((3,2,5,7), dtype=complex); y = np.arange(210, dtype=complex).reshape(3,2,5,7); z = np.arange(70.).reshape(2,5,7); w = np.arange(210.).reshape(3,2,5,7) + 3; t = np.arange(70., dtype=complex).reshape(2,5, 7) + 1 ; u = np.arange(210.).reshape(3,2,5,7) + 8; add_pressure_diffusion(x,y,z,w,t,u,3.)

#pythran export cross1(float[:,:,:,:], float[:,:,:,:], float[:,:,:,:])
def cross1(c, a, b):
    c[0] = a[0] * b[2] - a[2] * b[1]
    c[1] = a[2] * b[0] - a[0] * b[2]
    c[2] = a[0] * b[1] - a[1] * b[0]
    return c

#pythran export cross2(complex[:,:,:,:], float[:,:,:,:], complex[:,:,:,:])
#pythran export cross2(complex[:,:,:,:], int64[:,:,:,:], complex[:,:,:,:])
def cross2(c, a, b):
    cross1(c, a, b)
    c *= 1j
    return c

#pythran export add_pressure_diffusion(
#    complex[:,:,:,:], complex[:,:,:,:],
#    float[:,:,:], float[:,:,:,:], complex[:,:,:],
#    float[:,:,:,:], float)
def add_pressure_diffusion(dU, U_hat, K2, K, P_hat, K_over_K2, nu):
    du0, du1, du2 = dU[0], dU[1], dU[2]
    k_0, k_1, k_2 = K_over_K2[0], K_over_K2[1], K_over_K2[2]
    P_hat[:] = du0*k_0+du1*k_1+du2*k_2
    dU[:] = dU - P_hat*K - nu*K2*U_hat
    return P_hat
