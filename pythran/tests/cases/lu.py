#runas import numpy as np; x = np.arange(25.).reshape(5,5); factorMatrix0(x), factorMatrix1(x)

import numpy as np
#pythran export factorMatrix0(float[:,:])
def factorMatrix0(M):
# Gaussian elimination, partial pivoting.
# M must be an (n,n+1) numpy array. Not tested!
    n = M.shape[0]
    m=  M.shape[1]
    for line in range(0, n-1):
        # find pivot
        cmax = np.argmax(abs(M[line:n,line])) + line

        # exchange rows if necessary
        if cmax != line:
            M[[line,cmax]]=M[[cmax,line]]

        # eliminate
        pivot = M[line,line]
        for j in range(line+1,n):
            v= M[j,line]/pivot
            for k in range(line,m):
                M[j,k]-= v*M[line,k]

#pythran export factorMatrix1(float[:,:])
def factorMatrix1(M):
# Gaussian elimination, partial pivoting.
# M must be an (n,n+1) numpy array. Not tested!
    n = M.shape[0]
    m=  M.shape[1]
    for line in range(0, n-1):
        # find pivot
        cmax=line
        vmax= abs(M[line,line])
        for i in range(line+1,n):
            if abs(M[i,line])> vmax:
                vmax= abs(M[i,line])
                cmax= i
        # exchange rows if necessary
        if cmax != line:
            for j in range(line,m):
                t= M[line,j]
                M[line,j]= M[cmax,j]
                M[cmax,j]= t
        # eliminate
        pivot = M[line,line]
        for j in range(line+1,n):
            v= M[j,line]/pivot
            for k in range(line,m):
                M[j,k]-= v*M[line,k]
