#from http://rosettacode.org/wiki/Repeat_a_string
#pythran export test(int)
#runas test(5)

def test(n):
    return "ha" * n, n * "ha"
