import math

def some_work():
    sum = 0;
    for i in xrange(0, 1000):
        sum += math.sqrt (i)

def omp_parallel_for_private():
    sum = 0
    i2 = 0

    'omp parallel for reduction(+: sum) schedule(static, 1) private(i) private(i2)'
    for i in xrange(1, 1001):
        i2 = i
        'omp flush'
        some_work()
        'omp flush'
        sum += i2

    known_sum = (1000 * (1000 + 1)) / 2
    return known_sum == sum;
