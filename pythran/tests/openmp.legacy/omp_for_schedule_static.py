import omp
from time import sleep

def omp_for_schedule_static():
    NUMBER_OF_THREADS = 10
    CFSMAX_SIZE = 10000
    MAX_TIME = 0.01

    SLEEPTIME = 0.0005


    counter = 0
    tmp_count=1
    lastthreadsstarttid = -1
    result = 1
    chunk_size = 7

    tids = [0] * (CFSMAX_SIZE + 1)
    notout = 1
    maxiter = 0

    #omp parallel shared(tids,counter), num_threads(NUMBER_OF_THREADS)
    #omp single
    threads = omp.get_num_threads ()

    if threads < 2:
        print("This test only works with at least two threads");
        return True
    tids[CFSMAX_SIZE] = -1
    if "omp parallel shared(tids) num_threads(NUMBER_OF_THREADS)":
        tid = omp.get_thread_num ();

        #omp for nowait schedule(static,chunk_size)
        for j in range(CFSMAX_SIZE):
            count = 0.
            #pragma omp flush(maxiter)
            if j > maxiter:
                #pragma omp critical
                maxiter = j
            while notout and (count < MAX_TIME) and (maxiter == j):
                #pragma omp flush(maxiter,notout)
                sleep (SLEEPTIME)
                count += SLEEPTIME
            tids[j] = tid

        notout = 0
        #omp flush(maxiter,notout)

    # analysing the data in array tids

    lasttid = tids[0]
    tmp_count = 0;

    print(lasttid)
    print(tids)
    for i in range(CFSMAX_SIZE):
        # If the work  was done by the same thread increase tmp_count by one.
        if tids[i] == lasttid:
            tmp_count+=1
            continue;

        # Check if the next thread had has the right thread number. When finding
        # threadnumber -1 the end should be reached.
        if (tids[i] == (lasttid + 1) % threads or tids[i] == -1):
            # checking for the right chunk size
            if (tmp_count == chunk_size):
                tmp_count = 1
                lasttid = tids[i]
            # If the chunk size was wrong, check if the end was reached 
            else:
                if (tids[i] == -1):
                    if (i == CFSMAX_SIZE):
                        print("Last thread had chunk size ", tmp_count)
                        break;
                    else:
                        print("ERROR: Last thread (thread with number -1) was found before the end.")
                        result = 0
                else:
                    print("ERROR: chunk size was . (assigned was )\n", tmp_count, chunk_size)
                    result = 0
        else:
            print("ERROR: Found thread with number %d (should be inbetween 0 and %d).", tids[i], threads - 1)
            result = 0;

    return result
