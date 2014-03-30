def omp_parallel_default():
    import omp
    sum = 0
    known_sum = (1000 * (1000 + 1)) / 2

    if "omp parallel default(shared)":
        mysum = 0
        'omp for'
        for i in xrange(1, 1001):
            mysum += i

        if 'omp critical':
            sum += mysum

    return known_sum == sum
