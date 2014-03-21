#from http://rosettacode.org/wiki/Price_fraction#Python
#pythran export pricerounder(float)
#runas map(pricerounder, [0.3793, 0.4425, 0.0746, 0.6918, 0.2993, 0.5486, 0.7848, 0.9383, 0.2292, 0.9560])

import bisect
def pricerounder(pricein):
    _cout = [.10, .18, .26, .32, .38, .44, .50, .54, .58, .62, .66, .70, .74, .78, .82, .86, .90, .94, .98, 1.00]
    _cin  = [.06, .11, .16, .21, .26, .31, .36, .41, .46, .51, .56, .61, .66, .71, .76, .81, .86, .91, .96, 1.01]
    return _cout[ bisect.bisect_right(_cin, pricein) ]
