def omp_barrier():
    import omp
    result1 = 0
    result2 = 0
    if 'omp parallel private(rank)':
        rank = omp.get_thread_num()
        if rank <= 1:
            for result2 in range(10000):
                pass
        'omp barrier'
        if rank == 2 or rank == 0:
            result1 = result2
    return result1 
