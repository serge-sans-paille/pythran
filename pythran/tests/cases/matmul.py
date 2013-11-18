#runas a=[ [ float(i) for i in xrange(60)] for j in xrange(60)] ; matrix_multiply(a,a)
#pythran export matrix_multiply(float list list, float list list)
def zero(n,m): return [[0 for row in xrange(n)] for col in xrange(m)]
def matrix_multiply(m0, m1):
    new_matrix = zero(len(m0),len(m1[0]))
    for i in xrange(len(m0)):
        for j in xrange(len(m1[0])):
            r=0
            "omp parallel for reduction(+:r)"
            for k in xrange(len(m1)):
                r += m0[i][k]*m1[k][j]
            new_matrix[i][j]=r
    return new_matrix
