import alias1 as a1
import alias2 as alias1
import alias2

#pythran export entry()
#runas entry()
def entry():
    return a1.add(1,2) + alias1.mul(10,2) + alias2.div(5, 2)
