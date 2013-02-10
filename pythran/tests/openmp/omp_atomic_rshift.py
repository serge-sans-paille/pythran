def omp_atomic_rshift():
    sum = 1024
    LOOPCOUNT = 10
    "omp parallel for"
    for i in xrange(LOOPCOUNT):
        "omp atomic"
        sum >>= 1
    return sum == 1
