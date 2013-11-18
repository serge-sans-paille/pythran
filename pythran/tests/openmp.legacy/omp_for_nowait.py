def omp_for_nowait():
    LOOPCOUNT = 1000
    myarray = [0]*LOOPCOUNT
    result = 0
    count = 0
    import omp
    if 'omp parallel private(rank)':
        rank = omp.get_thread_num()
        'omp for nowait'
        for i in range(LOOPCOUNT):
            if i == 0:
                while i < LOOPCOUNT**2: i+=1
                count = 1
                'omp flush(count)'
        for i in range(LOOPCOUNT):
            'omp flush(count)'
            if count ==0:
                result = 1
    return result == 1
