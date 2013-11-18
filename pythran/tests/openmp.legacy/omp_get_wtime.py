def omp_get_wtime():
    import omp
    from time import sleep
    wait_time = 1

    start = omp.get_wtime()
    sleep(wait_time)
    end = omp.get_wtime()
    measured_time = end - start

    return measured_time > 0.99 * wait_time and measured_time < 1.01 * wait_time
