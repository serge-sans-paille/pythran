def omp_task_private():
    sum = 0
    result = 0
    LOOPCOUNT = 1000
    NUM_TASKS = 25

    known_sum = (LOOPCOUNT * (LOOPCOUNT + 1)) / 2

    if 'omp parallel':
        if 'omp single':
            for i in xrange(0, NUM_TASKS):
                if 'omp task private(sum, j) shared(result, known_sum)':
                    sum = 0
                    for j in xrange(0, LOOPCOUNT + 1):
                        'omp flush'
                        sum += j
                    if sum != known_sum:
                        if 'omp critical':
                            result += 1
    return result == 0
