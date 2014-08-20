#pythran export list_comp(int list list)
#runas list_comp([[], [], [1]])

def foo(cc, x, y):
    for a in cc:
        if a:
            return True
        return False

def list_comp(cc):
    return [(x,y) for x in range(1) for y in range(2) if foo(cc, x, y)]
