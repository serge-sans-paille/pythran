#pythran export entry()
#runas entry()
def entry():
    import import_inside_function
    return import_inside_function.foo(1)
