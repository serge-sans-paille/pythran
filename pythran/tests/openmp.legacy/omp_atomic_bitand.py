def omp_atomic_bitand():
    sum = 0
    LOOPCOUNT = 1000
    logics = [1]*LOOPCOUNT
    "omp parallel for"
    for i in xrange(LOOPCOUNT):
        "omp atomic"
        sum &= logics[i]
    return sum == 0
