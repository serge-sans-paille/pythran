def omp_single():
    nr_threads_in_single = 0
    result = 0
    nr_iterations = 0
    LOOPCOUNT = 1000

    if 'omp parallel private(i)':
        for i in xrange(LOOPCOUNT):
            if 'omp single':
                'omp flush'
                nr_threads_in_single += 1
                'omp flush'
                nr_iterations += 1
                nr_threads_in_single -= 1
                result += nr_threads_in_single
    return result == 0 and nr_iterations == LOOPCOUNT
