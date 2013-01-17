# from the paper `using cython to speedup numerical python programs'
#pythran export timeloop(float, float, float, float, float, float array 2, float array 2, float array 2)
#runas import numpy ; A=[range(2000) for i in xrange(100)] ; B=[range(2000) for i in xrange(100)] ; C=[range(2000) for i in xrange(100)] ; a = numpy.array(A) ; b = numpy.array(B) ; c = numpy.array(C) ; timeloop(1,2,.01,.1,.18, a, b, c )

def timeloop(t, t_stop, dt, dx, dy, u, um, k):
    while t <= t_stop:
        t += dt
        new_u = calculate_u(dt, dx, dy, u, um, k)
        um = u
        u = new_u
    return u

import numpy

def calculate_u(dt, dx, dy, u, um, k):
    up = numpy.zeros(u.shape)
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

