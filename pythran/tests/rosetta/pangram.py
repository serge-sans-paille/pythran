#from http://rosettacode.org/wiki/Pangram_checker#Python
#pythran export ispangram(str)
#runas ispangram("The quick brown fox jumps over the lazy dog")
#runas ispangram("The brown fox jumps over the lazy dog")

import string

def ispangram(sentence, alphabet=string.ascii_lowercase):
    alphaset = set(alphabet)
    return alphaset <= set(sentence.lower())
