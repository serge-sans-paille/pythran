def omp_atomic_lshift():
    sum = 1
    LOOPCOUNT = 10
    "omp parallel for"
    for i in xrange(LOOPCOUNT):
        "omp atomic"
        sum <<= 1
    return sum == 2 ** LOOPCOUNT
