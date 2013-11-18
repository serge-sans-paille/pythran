def omp_get_num_threads():
    import omp
    nthreads = 0
    nthreads_lib = -1

    if 'omp parallel':
        if 'omp critical':
            nthreads += 1
        if 'omp single':
            nthreads_lib = omp.get_num_threads()

    return nthreads == nthreads_lib
