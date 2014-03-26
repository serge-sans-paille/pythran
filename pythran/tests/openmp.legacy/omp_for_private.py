def do_some_work():
    import math
    sum = 0.
    for i in range(1000):
        sum+=math.sqrt(i)

def omp_for_private():
    sum = 0
    sum0 = 0
    LOOPCOUNT = 1000
    if 'omp parallel':
        sum1 = 0
        'omp for private(sum0) schedule(static,1)'
        for i in range(1, LOOPCOUNT+1):
            sum0 = sum1
            'omp flush'
            sum0 += i
            do_some_work()
            'omp flush'
            sum1 = sum0
        'omp critical'
        sum += sum1
    known_sum = (LOOPCOUNT * (LOOPCOUNT + 1)) / 2
    return known_sum == sum
