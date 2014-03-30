def omp_task_imp_firstprivate():
    i = 5
    k = 0
    result = 0
    NUM_TASKS = 25
    task_result = 1

    if 'omp parallel firstprivate(i)':
        if 'omp single':
            for k in xrange(NUM_TASKS):
                if 'omp task  shared(result, task_result)':
                    if i != 5:
                        task_result = 0

                    for j in xrange(0, NUM_TASKS):
                        i += 1
            'omp taskwait'
            result = task_result and i == 5
    return result
