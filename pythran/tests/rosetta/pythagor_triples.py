#from http://rosettacode.org/wiki/Pythagorean_triples#Python
#pythran export triples(int)
#runas triples(10)
#runas triples(100)
#runas triples(1000)
#runas triples(10000)
#runas triples(100000)

def triples(lim, a = 3, b = 4, c = 5):
    l = a + b + c
    if l > lim: return (0, 0)
    return reduce(lambda x, y: (x[0] + y[0], x[1] + y[1]), [
            (1, lim / l),
            triples(lim,  a - 2*b + 2*c,  2*a - b + 2*c,  2*a - 2*b + 3*c),
            triples(lim,  a + 2*b + 2*c,  2*a + b + 2*c,  2*a + 2*b + 3*c),
            triples(lim, -a + 2*b + 2*c, -2*a + b + 2*c, -2*a + 2*b + 3*c) ])
