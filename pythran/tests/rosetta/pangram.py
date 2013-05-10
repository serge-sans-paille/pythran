#from http://rosettacode.org/wiki/Pangram_checker#Python

import string

def ispangram(sentence, alphabet=string.ascii_lowercase):
    alphaset = set(alphabet)
    return alphaset <= set(sentence.lower())

def test():
    return (ispangram("The quick brown fox jumps over the lazy dog"),
            ispangram("The brown fox jumps over the lazy dog"))
