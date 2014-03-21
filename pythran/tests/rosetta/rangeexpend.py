#from http://rosettacode.org/wiki/Range_expansion#Python
#pythran export rangeexpand(str)
#runas rangeexpand('-6,-3--1,3-5,7-11,14,15,17-20')

def rangeexpand(txt):
    lst = []
    for r in txt.split(','):
        if '-' in r[1:]:
            r0, r1 = r[1:].split('-', 1)
            lst += range(int(r[0] + r0), int(r1) + 1)
        else:
            lst.append(int(r))
    return lst
