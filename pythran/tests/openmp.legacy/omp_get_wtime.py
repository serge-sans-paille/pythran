def omp_get_wtime():
    import omp
    from time import sleep
    wait_time = 2

    #omp parallel
    in_parallel = omp.in_parallel()

    start = omp.get_wtime()
    sleep(wait_time)
    end = omp.get_wtime()
    measured_time = end - start
    print(measured_time, wait_time)

    return (measured_time > 0.9 * wait_time and measured_time < 1.1 * wait_time) or not in_parallel
