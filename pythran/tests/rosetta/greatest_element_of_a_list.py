#from http://rosettacode.org/wiki/Greatest_element_of_a_list#Python
def test():
    floatstrings = ['1\n', ' 2.3\n', '4.5e-1\n', '0.01e4\n', '-1.2']
    return max(float(x) for x in floatstrings)
