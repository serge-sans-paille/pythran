from mix_builtin_main import bar
import mix_builtin_main, numpy, math as m
from numpy import sin

def foo(a):
    return float(bar(a+42) + mix_builtin_main.foo(a) + m.floor(numpy.cos(a) + sin(a)))
