import omp
from time import sleep


def omp_for_schedule_guided():
    tids = range(1001)
    maxiter = 0
    result = True
    notout = True
    if 'omp parallel':
        if 'omp single':
            threads = omp.get_num_threads()

    if threads<2:
        print "This test only works with at least two threads"
        result = False

    if 'omp parallel shared(tids, maxiter) private(count, tid, j)':
        tid = omp.get_num_threads()
        'omp for nowait schedule(guided)'
        for j in xrange(1000):
            count = 0
            'omp flush(maxiter)'
            if j > maxiter:
                if 'omp critical':
                    maxiter = j
            'omp flush(notout, maxiter)'
            while notout and count < 0.0005 and maxiter == j:
                'omp flush(notout, maxiter)'
                sleep(0.0001)
                count += 0.0001
            tids[j] = tid

        notout = False
        'omp flush(maxiter, notout)'

    last_threadnr = tids[0]
    global_chunknr = 0
    local_chunknr = [0 for i in xrange(10)]
    openwork = 1000;
    tids[1000] = -1

    for i in xrange(1,1001):
        if last_threadnr == tids[i]:
            pass
        else:
            global_chunknr += 1
            local_chunknr[last_threadnr] += 1
            last_threadnr = tids[i]

    chuncksize = range(global_chunknr)

    global_chunknr = 0
    determined_chunksize = 1
    last_threadnr = tids[0]

    for i in xrange(1,1001):
        if last_threadnr == tids[i]:
            determined_chunksize += 1
        else:
            chuncksize[global_chunknr] = determined_chunksize
            global_chunknr += 1
            local_chunknr[last_threadnr] += 1
            last_threadnr = tids[i]
            determined_chunksize = 1
        
    expected_chunk_size = openwork / threads
    c = chuncksize[0] / expected_chunk_size

    for i in xrange(global_chunknr):
        if expected_chunk_size > 1:
            expected_chunk_size = c * openwork / threads
        if abs(chuncksize[i] - expected_chunk_size) >= 2:
            result = False

        openwork -=chuncksize[i]
    return result
