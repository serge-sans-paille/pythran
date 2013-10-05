#runas solve()
#unittest.skip type can't be deducte
#pythran export solve()
def solve():
    '''
    In the card game poker, a hand consists of five cards and are ranked, from lowest to highest, in the following way:
    
    High Card: Highest value card.
    One Pair: Two cards of the same value.
    Two Pairs: Two different pairs.
    Three of a Kind: Three cards of the same value.
    Straight: All cards are consecutive values.
    Flush: All cards of the same suit.
    Full House: Three of a kind and a pair.
    Four of a Kind: Four cards of the same value.
    Straight Flush: All cards are consecutive values of same suit.
    Royal Flush: Ten, Jack, Queen, King, Ace, in same suit.
    The cards are valued in the order:
    2, 3, 4, 5, 6, 7, 8, 9, 10, Jack, Queen, King, Ace.
    
    If two players have the same ranked hands then the rank made up of the highest value wins; for example, a pair of eights beats a pair of fives (see example 1 below). But if two ranks tie, for example, both players have a pair of queens, then highest cards in each hand are compared (see example 4 below); if the highest cards tie then the next highest cards are compared, and so on.
    
    Consider the following five hands dealt to two players:
    
    Hand        Player 1            Player 2          Winner
    1       5H 5C 6S 7S KD      2C 3S 8S 8D TD      Player 2
            Pair of Fives       Pair of Eights
    
    2       5D 8C 9S JS AC      2C 5C 7D 8S QH      Player 1
            Highest card Ace    Highest card Queen
    
    3       2D 9C AS AH AC      3D 6D 7D TD QD      Player 2
            Three Aces          Flush with Diamonds
    
    4       4D 6S 9H QH QC      3D 6D 7H QD QS      Player 1
            Pair of Queens      Pair of Queens
            Highest card Nine   Highest card Seven
    
    5       2H 2D 4C 4D 4S      3C 3D 3S 9S 9D      Player 1
            Full House          Full House
            With Three Fours    with Three Threes
    
    The file, poker.txt, contains one-thousand random hands dealt to two players. Each line of the file contains ten cards (separated by a single space): the first five are Player 1's cards and the last five are Player 2's cards. You can assume that all hands are valid (no invalid characters or repeated cards), each player's hand is in no specific order, and in each hand there is a clear winner.
    
    How many hands does Player 1 win?
    '''
    
    value = { '2':2,'3':3,'4':4,'5':5,'6':6,'7':7,'8':8,'9':9,'T':10,'J':11,'Q':12,'K':13,'A':14 }
    all_kinds = tuple(reversed(sorted(value.values())))
    all_suits = list('DCSH')
    
    def make_hand(cards):
        hand = {}
        for card in cards:
            hand.setdefault(value[card[0]], {})[card[1]] = 1
            hand.setdefault(card[1], {})[value[card[0]]] = 1
        return hand
    
    def get(hash, arr): return ((i, hash.get(i, {})) for i in arr)
    def has(hash, arr): return not sum(1 for i in arr if i not in hash)
    
    def rank(hand):
        # Royal flush
        for suit, kinds in get(hand, all_suits):
            if has(kinds, tuple('TJQKA')):
                return (9,0,0)
    
        # Straight flush
        for suit, kinds in get(hand, all_suits):
            kinds = sorted(kind for kind in kinds.keys())
            if len(kinds) == 5 and kinds[4] - kinds[0] == 4:
                return (8, kinds[0],0)
    
        # Four of a kind
        for kind, suits in get(hand, all_kinds):
            if len(suits.keys()) == 4:
                return (7, kind,0)
    
        # Full house
        for kind, suits in get(hand, all_kinds):
            if len(suits.keys()) == 3:
                for kind2, suits2 in get(hand, all_kinds):
                    if len(suits2.keys()) == 2:
                        return (6, kind, kind2)
    
        # Flush
        for suit, kinds in get(hand, all_suits):
            if len(kinds.keys()) == 5:
                return (5,0,0)
    
        # Straight
        kinds = sorted(kind for kind in all_kinds if hand.has_key(kind))
        if len(kinds) == 5 and kinds[4] - kinds[0] == 4:
            return (4, kinds[0],0)
    
        # Three of a kind
        for kind, suits in get(hand, all_kinds):
            if len(suits.keys()) == 3:
                return (3, kind,0)
    
        # Two pairs
        for kind, suits in get(hand, all_kinds):
            if len(suits.keys()) == 2:
                for kind2, suits2 in get(hand, all_kinds):
                    if kind != kind2 and len(suits2.keys()) == 2:
                        return (2, kind, kind2)
    
        # One pair
        for kind, suits in get(hand, all_kinds):
            if len(suits.keys()) == 2:
                return (1, kind,0)
    
        for kind in all_kinds:
            if kind in hand:
                return (0, kind,0)
    
        return (0,0,0)
    
    
    count = 0
    for hand in open('poker.txt'):
        hands = hand.split(' ')
        p1, p2 = make_hand(hands[0:5]), make_hand(hands[5:10])
        v1, v2 = rank(p1), rank(p2)
        if v1 > v2: count += 1
    return count

