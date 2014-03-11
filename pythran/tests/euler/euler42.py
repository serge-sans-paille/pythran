#runas solve()
#pythran export solve()
def solve():
    '''
    The nth term of the sequence of triangle numbers is given by, t_n = 1/2 x n(n+1); so the first ten triangle numbers are:
    
    1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...
    
    By converting each letter in a word to a number corresponding to its alphabetical position and adding these values we form a word value. For example, the word value for SKY is 19 + 11 + 25 = 55 = t_10. If the word value is a triangle number then we shall call the word a triangle word.
    
    Using words.txt (right click and 'Save Link/Target As...'), a 16K text file containing nearly two-thousand common English words, how many are triangle words?
    
    '''
    def worth(word): return sum(ord(letter) - ord('A') + 1 for letter in word)

    words = open('euler/words42.txt').read().replace('"', '').split(',')
    triangle_numbers = dict.fromkeys(list(n*(n+1)/2 for n in xrange(1, 100)), 1)

    return sum(1 for word in words if worth(word) in triangle_numbers)

