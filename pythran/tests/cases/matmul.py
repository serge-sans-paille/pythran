#runas a=[ [ float(1) for i in xrange(200)] for j in xrange(200)] ; matrix_multiply(a,a)
#pythran export matrix_multiply(float list list, float list list)
def zero(n,m): return [[0 for row in xrange(n)] for col in xrange(m)]
def matrix_multiply(m0, m1):
    new_matrix = zero(len(m0),len(m1[0]))
    for i in xrange(len(m0)):
        for j in xrange(len(m1[0])):
            for k in xrange(len(m1)):
                new_matrix[i][j] += m0[i][k]*m1[k][j]
    return new_matrix
