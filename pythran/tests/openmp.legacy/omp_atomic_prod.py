def omp_atomic_prod():
    sum = 1
    LOOPCOUNT = 10
    "omp parallel for"
    for i in xrange(1,LOOPCOUNT):
        "omp atomic"
        sum *= i
    return sum == 362880
