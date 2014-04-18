#from http://www.emoticode.net/python/python-implementation-of-rc4-algorithm.html
#runas data = "e"*100 ; key = "f"*3 ; rc4_crypt(data, key)
#bench data = "e"*2000000 ; key = "f"*3 ; rc4_crypt(data, key)
#pythran export rc4_crypt(str, str)

#RC4 Implementation
def rc4_crypt( data , key ):

    S = range(256)
    j = 0
    out = []

    #KSA Phase
    for i in range(256):
        j = (j + S[i] + ord( key[i % len(key)] )) % 256
        S[i] , S[j] = S[j] , S[i]

    #PRGA Phase
    for char in data:
        i = j = 0
        i = ( i + 1 ) % 256
        j = ( j + S[i] ) % 256
        S[i] , S[j] = S[j] , S[i]
        out.append(chr(ord(char) ^ S[(S[i] + S[j]) % 256]))

    return ''.join(out)
