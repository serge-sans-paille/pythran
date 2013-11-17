def omp_parallel_firstprivate():
    sum = 0
    sum1 = 7
    num_threads = 0

    if 'omp parallel firstprivate(sum1) private(i)':
        'omp for'
        for i in xrange(1,1000):
            sum1 += i

        if 'omp critical':
            sum += sum1
            num_threads += 1

    known_sum = (999 * 1000) / 2 + 7 * num_threads
    return sum == known_sum
