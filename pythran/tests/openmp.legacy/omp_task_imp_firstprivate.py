import omp
def omp_task_imp_firstprivate():
    i = 5
    k = 0
    result = False
    NUM_TASKS = 25
    task_result = True

    if 'omp parallel firstprivate(i)':
        in_parallel = omp.in_parallel()
        if 'omp single':
            for k in range(NUM_TASKS):
                if 'omp task  shared(result, task_result)':
                    if i != 5:
                        task_result = False

                    for j in range(0, NUM_TASKS):
                        i += 1
            'omp taskwait'
            result = task_result and i == 5
    return result or not in_parallel
