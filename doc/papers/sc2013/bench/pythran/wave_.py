# from the paper `using cython to speedup numerical python programs'
#pythran export wave(float, float, float, float, float, float [] [], float [] [], float [] [])
#runas A=[map(float,range(2000)) for i in xrange(100)] ; B=[map(float,range(2000)) for i in xrange(100)] ; C=[map(float,range(2000)) for i in xrange(100)] ; import numpy ; A = numpy.array(A) ; B = numpy.array(B) ; C = numpy.array(C) ; wave(1,2,.01,.1,.18, A,B,C )
def wave(t, t_stop, dt, dx, dy, u, um, k):
    while t <= t_stop:
        t += dt
        new_u = calculate_u(dt, dx, dy, u, um, k)
        um = u
        u = new_u
    return u
import numpy

def calculate_u(dt, dx, dy, u, um, k):
    up = numpy.zeros((u.shape[0], u.shape[1]))
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

