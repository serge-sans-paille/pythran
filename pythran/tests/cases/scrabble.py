#from http://stackoverflow.com/questions/18345202/functional-vs-imperative-style-in-python
#pythran export scrabble_fun_score(str, str: int dict)
#pythran export scrabble_imp_score(str, str: int dict)
#runas scrabble_fun_score('tralala', {'t': 1, 'r': 2, 'a': 3, 'l': 4})
#runas scrabble_fun_score('tralala', {'t': 1, 'r': 2, 'a': 3, 'l': 4})
#bench import string; import random; a = "".join([random.choice(string.letters) for i in xrange(12000000)]); v = dict(zip(string.letters, range(1000))); scrabble_fun_score(a, v)

def scrabble_fun_score(word, scoretable):
    return sum([scoretable.get(x, 0) for x in word])


def scrabble_imp_score(word, scoretable):
    score = 0
    for letter in word:
        if letter in scoretable:
            score += scoretable[letter]
    return score
