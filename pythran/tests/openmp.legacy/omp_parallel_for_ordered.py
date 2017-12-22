def check_i_islarger2(i, last_i):
    islarger = i > last_i
    last_i = i
    return islarger, last_i

def omp_parallel_for_ordered():
    sum = 0
    is_larger = True
    last_i = 0

    'omp parallel for schedule(static, 1) ordered'
    for i in range(1,100):
        ii = i
        if 'omp ordered':
            tmp_is_larger, last_i = check_i_islarger2(i, last_i)
            is_larger = tmp_is_larger and is_larger
            sum += ii

    known_sum = (99 * 100) / 2
    return known_sum == sum and is_larger
