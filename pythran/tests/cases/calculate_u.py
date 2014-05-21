# from the paper `using cython to speedup numerical python programs'
#pythran export timeloop(float, float, float, float, float, float list list, float list list, float list list)
#bench A=[range(70) for i in xrange(100)] ; B=[range(70) for i in xrange(100)] ; C=[range(70) for i in xrange(100)] ; timeloop(1,2,.01,.1,.18, A,B,C )
#runas A=[range(20) for i in xrange(10)] ; B=[range(20) for i in xrange(10)] ; C=[range(20) for i in xrange(10)] ; timeloop(1,2,.01,.1,.18, A,B,C )
def timeloop(t, t_stop, dt, dx, dy, u, um, k):
    while t <= t_stop:
        t += dt
        new_u = calculate_u(dt, dx, dy, u, um, k)
        um = u
        u = new_u
    return u

def calculate_u(dt, dx, dy, u, um, k):
    up = [ [0.]*len(u[0]) for i in xrange(len(u)) ]
    "omp parallel for"
    for i in xrange(1, len(u)-1):
        for j in xrange(1, len(u[0])-1):
            up[i][j] = 2*u[i][j] - um[i][j] + \
                (dt/dx)**2*(
                        (0.5*(k[i+1][j] + k[i][j])*(u[i+1][j] - u[i][j]) -
                            0.5*(k[i][j] + k[i-1][j])*(u[i][j] - u[i-1][j]))) + \
                        (dt/dy)**2*(
                                (0.5*(k[i][j+1] + k[i][j])*(u[i][j+1] - u[i][j]) -
                                    0.5*(k[i][j] + k[i][j-1])*(u[i][j] - u[i][j-1])))
    return up
