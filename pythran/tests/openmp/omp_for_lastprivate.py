def omp_for_lastprivate():
    sum = 0
    i0 = -1
    LOOPCOUNT = 1000
    if 'omp parallel private(sum0)':
        sum0 = 0
        'omp for schedule(static,7) lastprivate(i0)'
        for i in range(1, LOOPCOUNT + 1):
            sum0 += i
            i0 = i
        'omp critical'
        sum+=sum0
    known_sum = (LOOPCOUNT * (LOOPCOUNT + 1)) / 2
    return (sum == known_sum) and (i0 == LOOPCOUNT)
