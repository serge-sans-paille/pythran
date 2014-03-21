#from http://rosettacode.org/wiki/100_doors#Python
#pythran export unoptimized()
#runas unoptimized()
#pythran export optimized()
#runas optimized()
#pythran export one_liner_list_comprehension()
#runas one_liner_list_comprehension()
#pythran export one_liner_generator_comprehension()
#runas one_liner_generator_comprehension()

def unoptimized():
    doors = [False] * 100
    for i in xrange(100):
        for j in xrange(i, 100, i+1):
            doors[j] = not doors[j]
        print "Door %d:" % (i+1), 'open' if doors[i] else 'close'

def optimized():
    for i in xrange(1, 101):
        root = i ** 0.5
        print "Door %d:" % i, 'open' if root == int(root) else 'close'

def one_liner_list_comprehension():
    print '\n'.join(['Door %s is %s' % (i, ['closed', 'open'][(i**0.5).is_integer()]) for i in xrange(1, 10001)])

def one_liner_generator_comprehension():
    print '\n'.join('Door %s is %s' % (i, 'closed' if i**0.5 % 1 else 'open') for i in range(1, 101))
