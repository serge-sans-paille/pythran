def omp_for_schedule_auto():
    import omp
    sum = 0
    sum0 = 12345
    sum1 = 0
    if 'omp parallel private(i, sum1)':
        if 'omp single':
            threadsnum = omp.get_num_threads()
        'omp for firstprivate(sum0) schedule(auto)'
        for i in xrange(1, 1001):
            sum0 += i
            sum1 = sum0
        if 'omp critical':
            sum += sum1
    known_sum = 12345 * threadsnum + (1000 * (1000 + 1)) / 2
    return known_sum == sum
