def omp_parallel_for_if():
    using = 0
    num_threads = 0
    import omp
    sum = 0
    sum2 = 0
    LOOPCOUNT=1000
    'omp parallel for private(i) if(using == 1)'
    for i in range(LOOPCOUNT+1):
        num_threads = omp.get_num_threads()
        sum+=i
    known_sum = (LOOPCOUNT * (LOOPCOUNT + 1)) / 2
    return known_sum == sum and num_threads == 1
