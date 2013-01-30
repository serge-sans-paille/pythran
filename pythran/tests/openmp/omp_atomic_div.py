def omp_atomic_div():
    sum = 362880
    LOOPCOUNT = 10
    "omp parallel for"
    for i in xrange(1,LOOPCOUNT):
        "omp atomic"
        sum /= i
    return sum == 1
