#runas solve(1, 1000)
#pythran export solve(int, int)
#FIXME unittest.skip conflicting name for end
def solve(start, end):
    '''
    How many letters would be needed to write all the numbers in words from 1 to 1000?
    '''

    words = [
        (   1,  'one'      , ''     ),
        (   2,  'two'      , ''     ),
        (   3,  'three'    , ''     ),
        (   4,  'four'     , ''     ),
        (   5,  'five'     , ''     ),
        (   6,  'six'      , ''     ),
        (   7,  'seven'    , ''     ),
        (   8,  'eight'    , ''     ),
        (   9,  'nine'     , ''     ),
        (  10,  'ten'      , ''     ),
        (  11,  'eleven'   , ''     ),
        (  12,  'twelve'   , ''     ),
        (  13,  'thirteen' , ''     ),
        (  14,  'fourteen' , ''     ),
        (  15,  'fifteen'  , ''     ),
        (  16,  'sixteen'  , ''     ),
        (  17,  'seventeen', ''     ),
        (  18,  'eighteen' , ''     ),
        (  19,  'nineteen' , ''     ),
        (  20,  'twenty'   , ''     ),
        (  30,  'thirty'   , ''     ),
        (  40,  'forty'    , ''     ),
        (  50,  'fifty'    , ''     ),
        (  60,  'sixty'    , ''     ),
        (  70,  'seventy'  , ''     ),
        (  80,  'eighty'   , ''     ),
        (  90,  'ninety'   , ''     ),
        ( 100,  'hundred'  , 'and'  ),
        (1000,  'thousand' , 'and'  ),
    ]
    words.reverse()

    def spell(n, words):
        word = []
        while n > 0:
            for num in words:
                if num[0] <= n:
                    div = n / num[0]
                    n = n % num[0]
                    if num[2]: word.append(' '.join(spell(div, words)))
                    word.append(num[1])
                    if num[2] and n: word.append(num[2])
                    break
        return word

    return sum(len(word) for n in xrange(start, end + 1) for word in spell(n, words))

