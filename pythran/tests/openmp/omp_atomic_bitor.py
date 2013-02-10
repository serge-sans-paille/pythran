def omp_atomic_bitor():
    sum = 0
    LOOPCOUNT = 1000
    logics = [1]*LOOPCOUNT
    logics[LOOPCOUNT/2] = 0
    "omp parallel for"
    for i in xrange(LOOPCOUNT):
        "omp atomic"
        sum |= logics[i]
    return sum == 1
