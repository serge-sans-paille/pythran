def omp_parallel_shared():
    sum = 0
    LOOPCOUNT = 1000
    known_sum = (LOOPCOUNT * (LOOPCOUNT + 1)) / 2
    if 'omp parallel shared(sum)':
        mysum = 0
        'omp for'
        for i in xrange(1, LOOPCOUNT + 1):
            mysum += i
        if 'omp critical':
            sum += mysum

    return known_sum == sum
