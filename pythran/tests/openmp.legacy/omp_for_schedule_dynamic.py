def omp_for_schedule_dynamic():
    CFDMAX_SIZE = 100
    chunk_size = 7
    tids = [0]*CFDMAX_SIZE
    count = 0
    tmp_count = 0
    result = 0
    import omp
    if 'omp parallel private(tid) shared(tids)':
        tid = omp.get_thread_num()
        'omp for schedule(dynamic, chunk_size)'
        for i in range(CFDMAX_SIZE):
            tids[i] = tid

    for i in range(CFDMAX_SIZE-1):
        if tids[i] != tids[i+1]:
            count +=1

    tmp = [1] * (count + 1)
    for i in range(CFDMAX_SIZE-1):
        if tids[i] != tids[i+1]:
            tmp_count+=1
            tmp[tmp_count] = 1
        else:
            tmp[tmp_count]+=1

    for i in range(count):
        if tmp[i]%chunk_size != 0:
            result+=1
    if tmp[count]%chunk_size != CFDMAX_SIZE%chunk_size:
        result+=1
    return result == 0
