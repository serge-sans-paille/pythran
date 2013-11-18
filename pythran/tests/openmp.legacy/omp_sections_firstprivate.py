def omp_sections_firstprivate():
    sum = 7
    sum0 = 11

    if 'omp parallel':
        if 'omp sections firstprivate(sum0)':
            if 'omp section':
                if 'omp critical':
                    sum += sum0
            if 'omp section':
                if 'omp critical':
                    sum += sum0
            if 'omp section':
                if 'omp critical':
                    sum += sum0
    known_sum=11*3+7
    return (known_sum==sum)
