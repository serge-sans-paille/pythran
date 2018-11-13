from .global_init import aa

def cc():
    return aa()


XX = [aa(), 3]

#pythran export bb()
def bb():
    return XX
