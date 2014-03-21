#from http://rosettacode.org/wiki/Greatest_element_of_a_list#Python
#pythran export test(str list)
#runas test(['1\n', ' 2.3\n', '4.5e-1\n', '0.01e4\n', '-1.2'])
#FIXME unittest.skip

def test(floatstrings):
    return max(float(x) for x in floatstrings)
