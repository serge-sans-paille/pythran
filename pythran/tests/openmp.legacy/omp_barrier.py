def omp_barrier():
    import omp
    from time import sleep
    result1 = 0
    result2 = 0
    #omp parallel num_threads(4)
    if 1:
        use_omp = omp.in_parallel()
        rank = omp.get_thread_num()
        if rank == 1:
            sleep(0.5)
            result2 = 3
        #omp barrier
        if rank == 2:
            result1 = result2
    if use_omp:
        return result1 == 3
    else:
        return result1 == 0
