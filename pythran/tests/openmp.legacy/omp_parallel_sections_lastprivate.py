def omp_parallel_sections_lastprivate():
    sum =0
    sum0 = 0
    i0 = -1
    if 'omp parallel sections private(sum0) lastprivate(i0)':
        if 'omp section':
            sum0 = 0
            for i in xrange(1, 400):
                sum0 += i
                i0 = i
            if 'omp critical':
                sum += sum0
        if 'omp section':
            sum0 = 0
            for i in xrange(400, 700):
                sum0 += i
                i0 = i
            if 'omp critical':
                sum += sum0
        if 'omp section':
            sum0 = 0
            for i in xrange(700, 1000):
                sum0 += i
                i0 = i
            if 'omp critical':
                sum += sum0

    known_sum = (999 * 1000) / 2
    return known_sum == sum and i0 == 999
