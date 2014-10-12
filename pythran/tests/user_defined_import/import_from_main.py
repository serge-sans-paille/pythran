from import_from1 import foo
from import_from2 import foo as foo2



#pythran export entry()
#runas entry()
def entry():
    return foo(1, 2) + foo2(1, 2)
