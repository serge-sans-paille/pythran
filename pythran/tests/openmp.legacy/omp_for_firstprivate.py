def omp_for_firstprivate():
    sum = 0
    sum0 = 12345
    sum1 = 0
    import omp
    LOOPCOUNT = 1000
    if 'omp parallel private(sum1)':
        'omp single'
        threadsnum = omp.get_num_threads()
        'omp for firstprivate(sum0)'
        for i in range(1, LOOPCOUNT+1):
            sum0+=i
            sum1 = sum0
        'omp critical'
        sum+=sum1
    known_sum = 12345* threadsnum+ (LOOPCOUNT * (LOOPCOUNT + 1)) / 2
    return sum == known_sum
