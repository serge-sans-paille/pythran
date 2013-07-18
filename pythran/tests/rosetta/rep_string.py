#from http://rosettacode.org/wiki/Rep-string#Python

def is_repeated(text):
    'check if the first part of the string is repeated throughout the string'
    for x in range(len(text)//2, 0, -1):
        if text.startswith(text[x:]): return x
    return 0

def reps(text):
    return [text[:x] for x in range(1, 1 + len(text) // 2)
    if text.startswith(text[x:])]

def test():
    matchstr = """\
1001110011
1110111011
0010010010
1010101010
1111111111
0100101101
0100100
101
11
00
1
 
  
  
  """
    for line in matchstr.split():
        ln = is_repeated(line)
        print('%s has a repetition length of %s i.e. %s' 
                % (line, ln, line[:ln] if ln else '*not* a rep-string'))
        print '%s has reps %s' % (line, reps(line))     
