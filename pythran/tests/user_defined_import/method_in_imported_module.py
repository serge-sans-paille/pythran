def aa(a):
    ret = []
    while a > 2:
        ret.append(0)
        a -=1
    return ret

def hh(value):
    ret = []
    while value > 0:
        a, b = _div_tuple(value, 10)
        ret.insert(0, 0)
        value = a
    return ret


def _div_tuple(base, div):
    a = base // div
    b = base % div
    return a, b
