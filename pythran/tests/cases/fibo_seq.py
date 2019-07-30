""" Nom recursive version of fibo. """
# pythran export fibo(int)
# runas fibo(7)


def fibo(n):
    """ fibonaccie compuation. """
    a, b = 1, 1
    for _ in range(n):
        a, b = a + b, a
    return a
