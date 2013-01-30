def omp_critical():
    sum = 0
    if 'omp parallel private(mysum)':
        mysum = 0
        'omp for'
        for i in range(1000):
            mysum += i
        'omp critical'
        sum += mysum
    return sum == 999 * 1000 / 2
