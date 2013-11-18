def omp_atomic_add():
    sum = 0
    LOOPCOUNT=1000
    "omp parallel for"
    for i in xrange(LOOPCOUNT):
        "omp atomic"
        sum += i
    return sum == (LOOPCOUNT * (LOOPCOUNT -1 ) ) /2
