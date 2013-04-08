def omp_task():
    import omp
    from time import sleep
    NUM_TASKS = 25
    tids = range(NUM_TASKS)
    
    if 'omp parallel private(myi)':
        for i in xrange(NUM_TASKS):
            myi = i
            if 'omp task':
                sleep(0.01)
                tids[myi] = omp.get_thread_num()
    for i in xrange(NUM_TASKS):
        if tids[0] != tids[i]:
            return True

    return False
