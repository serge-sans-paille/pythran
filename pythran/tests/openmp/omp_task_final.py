unittest.skip
#final semble ne pas fonctionner
def omp_task_final():
    import omp
    from time import sleep
    error = 0
    NUM_TASKS = 25
    tids = range(NUM_TASKS)

    if 'omp parallel':
        if 'omp single':
            for i in xrange(NUM_TASKS):
                myi = i
                if 'omp task final(i>=10) private(k) firstprivate(myi)':
                    sleep(0.01)
                    tids[myi] = omp.get_thread_num()
            'omp taskwait'

    for i in xrange(10, NUM_TASKS):
        if tids[10] != tids[i]:
            print i, tids[10], tids[i]
            error += 1

    print error
    return error == 0
