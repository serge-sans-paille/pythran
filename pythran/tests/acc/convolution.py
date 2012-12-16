#pythran export convolution(int list list)
def convolution(A):
    B = [range(len(A[0])) for _ in range(len(A))]
    m = len(A)
    n = len(A[0])

    c11 = 2.0
    c21 = 5.0
    c31 = -8.0
    c12 = -3.0
    c22 = 6.0
    c32 = -9.0
    c13 = 4.0
    c23 = 7.0
    c33 = 10.0
    for i in xrange(1, m - 1):
        for j in xrange(1, n - 1):
          B[i][j] = c11 * A[i - 1][j - 1] + c12 * A[i + 0][j - 1] + c13 * A[i + 1][j - 1]\
          + c21 * A[i - 1][j + 0] + c22 * A[i + 0][j + 0] + c23 * A[i + 1][j + 0]\
          + c31 * A[i - 1][j + 1] + c32 * A[i + 0][j + 1] + c33 * A[i + 1][j + 1]
    return B 
