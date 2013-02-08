def omp_get_wtick():
    import omp
    tick = omp.get_wtick()
    return tick > 0.0 and tick < 0.01

