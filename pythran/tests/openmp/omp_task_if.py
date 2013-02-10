def omp_task_if():
    from time import sleep
    count = 0
    condition_false = False

    if 'omp parallel':
        if 'omp single':
            if 'omp task if(condition_false) shared(count, result)':
                sleep(0.5)
                result = (count == 0)

            count = 1

    return result
