def omp_task_shared():
    i = 0
    k = 0
    result = 0
    NUM_TASKS = 25

    if 'omp parallel':
        if 'omp single':
            for k in xrange(0, NUM_TASKS):
                if 'omp task shared(i)':
                    'omp atomic'
                    i += 1
    result = i
    return result == NUM_TASKS
