def omp_sections_private():
    sum = 7
    sum0 = 0

    if 'omp parallel':
        if 'omp sections private(sum0)':
            if 'omp section':
                sum0 = 0
                for i in xrange(0, 400):
                    sum0 += i
                if 'omp critical':
                    sum += sum0
            if 'omp section':
                sum0 = 0
                for i in xrange(400, 700):
                    sum0 += i
                if 'omp critical':
                    sum += sum0
            if 'omp section':
                sum0 = 0
                for i in xrange(700, 1000):
                    sum0 += i
                if 'omp critical':
                    sum += sum0

    known_sum = (999 * 1000) / 2 + 7;
    return known_sum == sum
