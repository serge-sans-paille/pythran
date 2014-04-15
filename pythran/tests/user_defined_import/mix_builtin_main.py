import mix_builtin, numpy

def bar(a):
    return a+42

def foo(a):
    return a+2*42

#pythran export entry(int)
#runas entry(10)
def entry(a):
    return mix_builtin.foo(a)
