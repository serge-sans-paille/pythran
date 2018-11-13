import global_init as gi


XX = [gi.aa(), 3]

#pythran export bb()
def bb():
    return XX
