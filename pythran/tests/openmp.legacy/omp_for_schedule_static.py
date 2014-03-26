import omp
from time import sleep


def omp_for_schedule_static():
    tmp_count = 1
    result = True
    chunk_size = 7
    CFSMAX_SIZE = 1000
    tids = [0] * (CFSMAX_SIZE + 1)
    notout = True
    maxiter = 0

    if 'omp parallel shared(tids)':
        if 'omp single':
            threads = omp.get_num_threads()

    if threads < 2:
        print 'E: This test only works with at least two threads'
        return False

    tids[CFSMAX_SIZE] = -1

    if 'omp parallel shared(tids)':
        tid = omp.get_thread_num()

        'omp for nowait schedule(static,chunk_size)'
        for j in xrange(CFSMAX_SIZE):
            count = 0
            'omp flush(maxiter)'
            if j > maxiter:
                'omp critical'
                maxiter = j
            while notout and count < 0.01 and maxiter == j:
                'omp flush(maxiter,notout)'
                sleep(0.0005)
                count += 0.0005

            tids[j] = tid

        notout = False
        'omp flush(maxiter, notout)'

    lasttid = tids[0]
    tmp_count = 0

    for i in xrange(CFSMAX_SIZE + 1):
        if tids[i] == lasttid:
            tmp_count += 1
            continue
        if tids[i] == ((lasttid + 1)%threads) or (tids[i] == -1):
            if tmp_count == chunk_size:
                tmp_count = 1
                lastid = tids[i]
            else:
                if tids[i] == -1:
                    if i == CFSMAX_SIZE:
                        break
                    else:
                        print "E: Last thread (thread with number -1) was found before the end.\n"
                        result = False
                else:
                    print "E: chunk size was " + str(tmp_count) + ". (assigned was " + str(chunk_size) + ")\n"
                    result = False
        else:
            print "E: Found thread with number " + str(tids[i]) + " (should be inbetween 0 and " + str(threads - 1) + ").\n"
            result = False
    return result

