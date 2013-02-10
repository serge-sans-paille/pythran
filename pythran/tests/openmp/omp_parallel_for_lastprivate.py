def omp_parallel_for_lastprivate():
    sum = 0
    i0 = -1
    'omp parallel for reduction(+:sum) schedule(static,7) private(i) lastprivate(i0)'
    for i in xrange(1,1001):
        sum += i
        i0 = i

    known_sum = (1000 * (1000 + 1)) / 2
    return known_sum == sum and i0 == 1000
