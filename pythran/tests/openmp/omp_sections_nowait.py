def omp_sections_nowait():
    import omp
    from time import sleep
    result = False
    count = 0

    if 'omp parallel private(rank)':
        rank = omp.get_thread_num()

        if 'omp sections nowait':
            if 'omp section':
                sleep(0.01)
                count = 1
                'omp flush(count)'
            if 'omp section':
                pass

        if 'omp sections':
            if 'omp section':
                pass
            if 'omp section':
                if count == 0:
                    result = True
    return result
