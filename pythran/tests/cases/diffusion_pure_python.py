# Reference: http://continuum.io/blog/the-python-and-the-complied-python
#pythran export diffusePurePython(float [][], float [][], int)
#runas import numpy as np;lx,ly=(2**7,2**7);u=np.zeros([lx,ly],dtype=np.double);u[lx/2,ly/2]=1000.0;tempU=np.zeros([lx,ly],dtype=np.double);diffusePurePython(u,tempU,500)
#bench import numpy as np;lx,ly=(2**6,2**6);u=np.zeros([lx,ly],dtype=np.double);u[lx/2,ly/2]=1000.0;tempU=np.zeros([lx,ly],dtype=np.double);diffusePurePython(u,tempU,55)

import numpy as np


def diffusePurePython(u, tempU, iterNum):
    """
    Apply nested iteration for the Forward-Euler Approximation
    """
    mu = .1
    row = u.shape[0]
    col = u.shape[1]

    for n in range(iterNum):
        for i in range(1, row - 1):
            for j in range(1, col - 1):
                tempU[i, j] = u[i, j] + mu * (
                    u[i + 1, j] - 2 * u[i, j] + u[i - 1, j] +
                    u[i, j + 1] - 2 * u[i, j] + u[i, j - 1])
        for i in range(1, row - 1):
            for j in range(1, col - 1):
                u[i, j] = tempU[i, j]
                tempU[i, j] = 0.0
