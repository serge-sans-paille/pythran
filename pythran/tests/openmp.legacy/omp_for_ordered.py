def omp_for_ordered():
    sum = 0
    is_larger = 1
    last_i = 0
    if 'omp parallel':
        my_is_larger = 1
        'omp for schedule(static,1) ordered'
        for i in range(1,100):
            if 'omp ordered':
                my_is_larger &= i > last_i
                last_i = i
                sum += i
        'omp critical'
        is_larger &= my_is_larger
    known_sum = (99 * 100) / 2
    return known_sum == sum and is_larger
