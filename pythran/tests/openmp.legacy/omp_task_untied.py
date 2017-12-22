def omp_task_untied():
    import omp
    from time import sleep
    NUM_TASKS = 25
    start_id = [0 for _ in range(NUM_TASKS)]
    current_id = [0 for _ in range(NUM_TASKS)]
    count = 0

    if 'omp parallel':
        use_parallel = omp.in_parallel()
        if 'omp single':
            for i in range(NUM_TASKS):
                myi = i
                if 'omp task firstprivate(myi) untied':
                    sleep(0.01)
                    start_id[myi] = omp.get_thread_num()

                    'omp taskwait'

                    if start_id[myi] % 2 != 0:
                        sleep(0.01)
                        current_id[myi] = omp.get_thread_num()

    for i in range(NUM_TASKS):
        if current_id[i] == start_id[i]:
            count += 1

    return count < NUM_TASKS or not use_parallel
