import omp
from time import sleep


def omp_for_schedule_static_3():
    tmp_count = 1
    result = True
    chunk_size = 7
    tids = range(1001)
    notout = True
    maxiter = 0

    if 'omp parallel shared(tids)':
        if 'omp single':
            threads = omp.get_num_threads()

    if threads < 2:
        print "E: This test only works with at least two threads"
        return False

    tids[1000] = -1

    if 'omp parallel shared(tids)':
        tid = omp.get_thread_num()
        'omp for nowait schedule(static,chunk_size)'
        for j in xrange(1000):
            count = 0
            'omp flush(maxiter)'
            if j > maxiter:
                if 'omp critical':
                    maxiter = j

            while notout and count < 0.01 and maxiter == j:
                'omp flush(maxiter,notout)'
                sleep(0.0005)
                count += 0.0005

            tids[j] = tid

        notout = False
    lasttid = tids[0]
    tmp_count = 0
    for i in xrange(1001):
        if tids[i] == lasttid:
            tmp_count += 1
            continue

        if tids[i] == (lasttid + 1) % threads or tids[i] == -1:
            if tmp_count == chunk_size:
                tmp_count = 1
                lasttid = tids[i]
            else:
                if tids[i] == -1:
                    if i == 1000:
                        break;
                    else:
                        print "E: Last thread (thread with number -1) was\
found before the end.\n"
                        result = False
                else:
                    print "ERROR: chunk size was " + str(tmp_count) +\
                    ". (assigned was " + str(chunk_size) + ")\n"
                    result = False
        else:
            print "ERROR: Found thread with number " + str(tids[i]) +\
            " (should be inbetween 0 and " + str(threads - 1) + ").\n"
            result = False

    tids = range(1000)
    tids2 = range(1000)

    if 'omp parallel':
        'omp for schedule(static) nowait'
        for n in xrange(1000):
            if 1000 == n + 1:
                sleep(0.0005)
            tids[n] = omp.get_thread_num()
        'omp for schedule(static) nowait'
        for m in xrange(1, 1001):
            tids2[m-1] = omp.get_thread_num()

    for i in xrange(1000):
        if tids[i] != tids2[i]:
            print "E: Chunk no. " + str(i) + " was assigned once to thread " +\
            str(tids[i]) + " and later to thread " + str(tids2[i]) + ".\n"
            result = False
    return result
