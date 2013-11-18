def omp_taskwait():
    from time import sleep
    result1 = 0
    result2 = 0
    NUM_TASKS = 25
    array = [0 for _ in range(NUM_TASKS)]

    if 'omp parallel':
        if 'omp single':
            for i in xrange(NUM_TASKS):
                myi = i
                if 'omp task firstprivate(myi)':
                    sleep(0.01)
                    array[myi] = 1

            'omp taskwait'

            for i in xrange(NUM_TASKS):
                if array[i] != 1:
                    result1 += 1

            for i in xrange(NUM_TASKS):
                myi = i
                if 'omp task firstprivate(myi)':
                    array[myi] = 2

    for i in xrange(NUM_TASKS):
        if array[i] != 2:
            result2 += 1

    return result1 == 0 and result2 == 0
