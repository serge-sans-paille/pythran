def omp_parallel_private():
    sum = 0
    num_threads = 0

    if 'omp parallel private(sum1, i)':
        sum1 = 7
        'omp for'
        for i in xrange(1, 1000):
            sum1 += i

        if 'omp critical':
            sum += sum1
            num_threads += 1

    known_sum = (999 * 1000) / 2 + 7 * num_threads

    return known_sum == sum
