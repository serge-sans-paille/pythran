#runas import numpy ; a = numpy.zeros((2000,2000)) ; convolution(a)
#pythran export convolution(float array 2)
import numpy as np
def convolution(A):
    B = np.zeros(A.shape)
    m = A.shape[0]
    n = A.shape[1]

    c11 = 2.0
    c21 = 5.0
    c31 = -8.0
    c12 = -3.0
    c22 = 6.0
    c32 = -9.0
    c13 = 4.0
    c23 = 7.0
    c33 = 10.0
    "omp parallel for private(i,j)"
    for i in xrange(1, m - 1):
        for j in xrange(1, n - 1):
          B[i,j] = c11 * A[i - 1,j - 1] + c12 * A[i + 0,j - 1] + c13 * A[i + 1,j - 1]\
          + c21 * A[i - 1,j + 0] + c22 * A[i + 0,j + 0] + c23 * A[i + 1,j + 0]\
          + c31 * A[i - 1,j + 1] + c32 * A[i + 0,j + 1] + c33 * A[i + 1,j + 1]
    return B
