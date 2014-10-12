import diamond_1, diamond_2

#pythran export entry()
#runas entry()

def entry():
    return diamond_1.foo(42) + diamond_2.foo(42)
