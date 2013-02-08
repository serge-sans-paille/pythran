def omp_single_nowait():
    total_iterations = 0
    nr_iterations = 0
    LOOPCOUNT = 1000

    if 'omp parallel private(i)':
        for i in xrange(LOOPCOUNT):
            if 'omp single nowait':
                'omp atomic'
                nr_iterations += 1

    if 'omp parallel private(i, my_iterations)':
        my_iterations = 0
        for i in xrange(LOOPCOUNT):
            if 'omp single nowait':
                my_iterations += 1
        if 'omp critical':
            total_iterations += my_iterations

    return nr_iterations == LOOPCOUNT and total_iterations == LOOPCOUNT
