def omp_atomic_bitxor():
    sum = 0
    LOOPCOUNT = 1000
    logics = [0]*LOOPCOUNT
    "omp parallel for"
    for i in xrange(LOOPCOUNT):
        "omp atomic"
        sum ^= logics[i]
    return sum == 0
