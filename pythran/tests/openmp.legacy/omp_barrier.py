def omp_barrier():
    import omp
    from time import sleep
    result1 = 0
    result2 = 0
    if 'omp parallel private(rank)':
        rank = omp.get_thread_num()
        if rank == 1:
            sleep(0.5)
            result2 = 3
        'omp barrier'
        if rank == 2:
            result1 = result2
    return result1 == 3
