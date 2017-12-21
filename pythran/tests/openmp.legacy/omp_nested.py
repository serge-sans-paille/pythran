def omp_nested():
    import omp
    counter = 0
    omp.set_nested(1)

    if 'omp parallel shared(counter) num_threads(4)':
        use_omp = omp.in_parallel()
        if 'omp critical':
            counter += 1

        if 'omp parallel num_threads(4)':
            if 'omp critical':
                counter -= 1
    return counter != 0 or not use_omp
