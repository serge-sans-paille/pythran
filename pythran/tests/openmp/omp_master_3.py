def omp_master_3():
    import omp
    tid_result = 0
    nthreads = 0
    executing_thread = -1
    
    if 'omp parallel private(tid)':
        if 'omp master':
            tid = omp.get_thread_num()
            if tid != 0:
                if 'omp critical':
                    tid_result += 1
            if 'omp critical':
                nthreads += 1
            executing_thread = omp.get_thread_num()
    return nthreads == 1 and executing_thread == 0 and tid_result == 0
