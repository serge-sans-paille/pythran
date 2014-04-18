#runas calc(60,100)
#bench calc(120,200)
#pythran export calc(int, int)
def update(u):
    dx = 0.1
    dy = 0.1
    dx2 = dx*dx
    dy2 = dy*dy
    nx, ny = len(u), len(u[0])
    for i in xrange(1,nx-1):
        for j in xrange(1, ny-1):
            u[i][j] = ((u[i+1][ j] + u[i-1][ j]) * dy2 +
                    (u[i][ j+1] + u[i][ j-1]) * dx2) / (2*(dx2+dy2))

def calc(N, Niter=100):
    u = [ [0]*N for _ in xrange(N)]
    u[0] = [1] * N
    for i in range(Niter):
        update(u)
    return u
