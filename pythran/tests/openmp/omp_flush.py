import omp
from time import sleep


def omp_flush():
    result1 = 0
    result2 = 0
    if 'omp parallel private(rank)':
        rank = omp.get_thread_num()
        'omp barrier'
        if rank == 1:
            result2 = 3
            'omp flush (result2)'
            dummy = result2
        if rank == 0:
            sleep(0.5)
            'omp flush(result2)'
            result1 = result2
    return result1 == result2 and result2 == dummy and result2 == 3
