#from http://jakascorner.com/blog/2016/08/omp-cancel.html

def has_zero(matrix):
    has_zero = False
    rows, cols = matrix.shape

    #omp parallel default(none) shared(matrix, has_zero)
    #omp for
    for row in range(rows):
        for col in range(cols):
            if matrix[row, col] == 0:
                #omp critical
                has_zero = True
                #omp cancel for

    return has_zero

import numpy as np
def cancel_for():
    data = np.array([[1,2,3], [4,0,5], [7, 8, 9]])
    res = has_zero(data)
    return res
