from .method_in_imported_module import aa, hh
from .other_method_in_imported_module import CC, DD

def cc():
    return aa(3)



#pythran export dd(int)
def dd(o):
    return hh(o)


XX = cc() + [3]
YY = CC()

#pythran export bb()
def bb():
    return XX, YY, DD()
