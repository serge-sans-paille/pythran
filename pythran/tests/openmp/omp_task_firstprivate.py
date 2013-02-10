def omp_task_firstprivate():
    sum = 1234
    result = 0
    LOOPCOUNT = 1000
    NUM_TASKS = 25

    known_sum = 1234 + (LOOPCOUNT * (LOOPCOUNT + 1)) / 2

    if 'omp parallel':
        if 'omp single':
            for i in xrange(NUM_TASKS):
                if 'omp task firstprivate(sum) private(j)':
                    for j in xrange(LOOPCOUNT + 1):
                        'omp flush'
                        sum += j
                    if sum != known_sum:
                        if 'omp critical':
                            result += 1

    return result == 0
