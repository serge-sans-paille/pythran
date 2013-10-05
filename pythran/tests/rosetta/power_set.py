#from http://rosettacode.org/wiki/Power_set#Python
def list_powerset(lst):
    # the power set of the empty set has one element, the empty set
    result = [[]]
    for x in lst:
        # for every additional element in our set
        # the power set consists of the subsets that don't
        # contain this element (just take the previous power set)
        # plus the subsets that do contain the element (use list
        # comprehension to add [x] onto everything in the
        # previous power set)
        result.extend([subset + [x] for subset in result])
    return result

# the above function in one statement
def list_powerset2(lst):
    return reduce(lambda result, x: result + [subset + [x] for subset in result],
            lst, [[]])

def p(l):
    if not l: return [[]]
    return p(l[1:]) + [[l[0]] + x for x in p(l[1:])]

def test():
    init = [1,2,3]
    return list_powerset(init), list_powerset2(init), p(init)
