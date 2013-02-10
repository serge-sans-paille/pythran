unittest.skip
#segfault ....
def omp_parallel_num_threads():
    import omp
    max_threads = 0
    failed = 0

    if 'omp parallel':
        if 'omp master':
            max_threads = omp.get_num_threads()

    for threads in xrange(1, max_threads + 1):
        nthreads = 0
        if 'omp parallel reduction(+:failed) num_threads(threads)':
            failed += (threads != omp.get_num_threads())
            'omp atomic'
            nthreads += 1
        failed += (nthreads != threads)

    return not failed
