#from http://rosettacode.org/wiki/Rep-string#Python
#pythran export is_repeated(str)
#pythran export reps(str)
#runas matchstr ="1001110011 1110111011 0010010010 1010101010 1111111111 0100101101 0100100 101 11 00 1"; [reps(i) for i in matchstr.split()]
#runas matchstr ="1001110011 1110111011 0010010010 1010101010 1111111111 0100101101 0100100 101 11 00 1"; [is_repeated(i) for i in matchstr.split()]

def is_repeated(text):
    'check if the first part of the string is repeated throughout the string'
    for x in range(len(text)//2, 0, -1):
        if text.startswith(text[x:]): return x
    return 0

def reps(text):
    return [text[:x] for x in range(1, 1 + len(text) // 2)
            if text.startswith(text[x:])]
