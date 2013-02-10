def omp_single_copyprivate():
    result = 0
    nr_iterations = 0
    LOOPCOUNT = 1000

    if 'omp parallel private(i, j)':
        for i in xrange(LOOPCOUNT):
            if 'omp single copyprivate(j)':
                nr_iterations += 1
                j = i
            if 'omp critical':
                result += j - i
            'omp barrier'
    return result == 0 and nr_iterations == LOOPCOUNT

