def omp_atomic_div():
    sum = 362880
    LOOPCOUNT = 10
    "omp parallel for"
    for i in range(1,LOOPCOUNT):
        "omp critical"
        sum /= i
    return sum == 1
