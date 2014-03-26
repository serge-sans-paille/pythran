def omp_single_private():
    nr_threads_in_single = 0
    nr_iterations = 0
    result = 0
    LOOPCOUNT = 1000

    if 'omp parallel':
        myresult = 0
        myit = 0
        for i in xrange(LOOPCOUNT):
            if 'omp single private(nr_threads_in_single)':
                nr_threads_in_single = 0
                'omp flush'
                nr_threads_in_single += 1
                'omp flush'
                myit += 1
                myresult += nr_threads_in_single
        if 'omp critical':
            result += nr_threads_in_single
            nr_iterations += myit

    return result == 0 and nr_iterations == LOOPCOUNT
