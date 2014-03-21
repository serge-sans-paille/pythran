#from http://rosettacode.org/wiki/Palindrome_detection#Python
#pythran export test()
#runas test()

def is_palindrome(s):
    return s == s[::-1]

def is_palindrome_r2(s):
    return not s or s[0] == s[-1] and is_palindrome_r2(s[1:-1])

def is_palindrome_r(s):
    if len(s) <= 1:
        return True
    elif s[0] != s[-1]:
        return False
    else:
        return is_palindrome_r(s[1:-1])

def test_(f, good, bad):
    if all(f(x) for x in good) and not any(f(x) for x in bad):
        print 'function passed all %d tests' % (len(good)+len(bad))

def test():
    pals = ['', 'a', 'aa', 'aba', 'abba']
    notpals = ['aA', 'abA', 'abxBa', 'abxxBa']
    test_(is_palindrome, pals, notpals)
    test_(is_palindrome_r, pals, notpals)
    test_(is_palindrome_r2, pals, notpals)
