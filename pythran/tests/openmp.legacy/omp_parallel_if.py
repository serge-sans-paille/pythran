def omp_parallel_if():
    control = 1
    sum = 0
    known_sum = (1000 * (1000 + 1)) / 2
    if 'omp parallel private(i) if(control==0)':
        mysum = 0
        for i in xrange(1,1001):
            mysum += i
        if 'omp critical':
            sum += mysum

    return sum == known_sum
