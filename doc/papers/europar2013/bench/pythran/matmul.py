#runas a=[ [ float(i) for i in xrange(600)] for j in xrange(600)] ; import numpy ; a = numpy.array(a) ; matrix_multiply(a,a)
#pythran export matrix_multiply(float[][], float[][])
import numpy
def matrix_multiply(m0, m1):
    new_matrix = numpy.zeros((m0.shape[0],m1.shape[1]))
    "omp parallel for private(i,j,k,r)"
    for i in xrange(m0.shape[0]):
        for j in xrange(m1.shape[1]):
            r=0
            for k in xrange(m1.shape[0]):
                r += m0[i,k]*m1[k,j]
            new_matrix[i,j]=r
    return new_matrix
