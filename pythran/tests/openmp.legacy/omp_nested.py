def omp_nested():
    import omp
    counter = 0
    omp.set_nested(1)

    if 'omp parallel shared(counter)':
        if 'omp critical':
            counter += 1

        if 'omp parallel':
            if 'omp critical':
                counter -= 1
    return counter != 0
