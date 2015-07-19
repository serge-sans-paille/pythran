""" Nom recursive version of fibo. """
# unittest.gmp.skip
# pythran export fibo(int)
# runas fibo(700)
# benchfibo(300000)


def fibo(n):
    """ fibonaccie compuation. """
    a, b = 1L, 1L
    for _ in range(n):
        a, b = a + b, a
    return a
