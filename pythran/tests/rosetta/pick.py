#from http://rosettacode.org/wiki/Pick_random_element#Python
#pythran export test()

def test():
    import random
    res = {"foo":0, "bar":0, "baz":0}
    for i in range(500):
        res[random.choice(res.keys())] += 1
    return res
