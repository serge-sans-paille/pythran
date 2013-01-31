def omp_master():
    import omp
    threads = 0
    executing_thread = -1

    if 'omp parallel':
        if 'omp master':
            if 'omp critical':
                threads += 1
            executing_thread = omp.get_thread_num()
    return threads == 1 and executing_thread == 0
