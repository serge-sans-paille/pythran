""" Checking if a number is a perfect square. """
# unittest.gmp.skip
# pythran export is_square(long)
# runas is_square(12345678987654321234567 ** 256)
# bench is_square(12345678987654321234567 ** 256)
# from http://stackoverflow.com/questions/2489435/\
# how-could-i-check-if-a-number-is-a-perfect-square


def is_square(a_positive_int):
    """ Check if it is a perfect square. """
    x = a_positive_int // 2
    seen = {x}
    while x * x != a_positive_int:
        x = (x + (a_positive_int // x)) // 2
        if x in seen:
            return False
        seen.add(x)
    return True
