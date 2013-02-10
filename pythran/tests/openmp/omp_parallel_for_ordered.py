def omp_parallel_for_ordered():
    sum = 0
    is_larger = True
    last_i = 0
    def check_i_islarger2(i_):
        islarger = i_ > last_i
        last_i = i_
        return islarger

    'omp parallel for schedule(static, 1) private(i, ii) ordered'
    for i in xrange(1,100):
        ii = i
        if 'omp ordered':
            is_larger = check_i_islarger2(i) and is_larger
            sum += ii

    known_sum = (99 * 100) / 2
    return known_sum == sum and is_larger
