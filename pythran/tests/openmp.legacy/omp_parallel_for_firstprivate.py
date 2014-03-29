def omp_parallel_for_firstprivate():
    sum = 0
    i2 = 3

    'omp parallel for reduction(+:sum) firstprivate(i2)'
    for i in xrange(1,1001):
        sum += i + i2

    known_sum = (1000 * (1000 + 1)) / 2 + i2 * 1000;
    return known_sum == sum
