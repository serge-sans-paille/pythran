#from http://rosettacode.org/wiki/Roman_numerals/Decode#Python
#runas decode('MCMXC')
#runas decode('MMVIII')
#runas decode('MDCLXVI')
#pythran export decode(str)

def decode( roman ):
    s, t = 'MDCLXVI', (1000, 500, 100, 50, 10, 5, 1)
    _rdecode = dict(zip(s, t))
    result = 0
    for r, r1 in zip(roman, roman[1:]):
        rd, rd1 = _rdecode[r], _rdecode[r1]
        result += -rd if rd < rd1 else rd
    return result + _rdecode[roman[-1]]
