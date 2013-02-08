def omp_parallel_sections_reduction(): 
    import math
    dt = 0.5
    rounding_error = 1.E-9

    sum = 7
    dsum = 0
    dt = 1. / 3.
    result = True
    product = 1
    logic_and = 1
    logic_or = 0
    bit_and = 1
    bit_or = 0
    exclusiv_bit_or = 0

    known_sum = (1000 * 999) / 2 + 7

    if 'omp parallel sections private(i) reduction(+:sum)':
        if 'omp section':   
            for i in xrange(1,300):
                sum += i
        if 'omp section':   
            for i in xrange(300,700):
                sum += i
        if 'omp section':   
            for i in xrange(700,1000):
                sum += i

    if known_sum != sum:
        print "E: reduction(+:sum)"
        result = False

    diff = (1000 * 999) / 2

    if 'omp parallel sections private(i) reduction(-:diff)':
        if 'omp section':   
            for i in xrange(1,300):
                diff -= i
        if 'omp section':   
            for i in xrange(300,700):
                diff -= i
        if 'omp section':   
            for i in xrange(700,1000):
                diff -= i

    if diff != 0:
        print "E: reduction(-:diff)"
        result = False

    dsum = 0
    dpt = 0
    for i in xrange(0, 20):
        dpt *= dt
    dknown_sum = (1 - dpt) / (1 - dt)

    if 'omp parallel sections private(i) reduction(+:dsum)':
        if 'omp section':
            for i in xrange(0,7):
                dsum += math.pow(dt, i)
        if 'omp section':
            for i in xrange(7,14):
                dsum += math.pow(dt, i)
        if 'omp section':
            for i in xrange(14,20):
                dsum += math.pow(dt, i)

    if abs(dsum-dknown_sum) > rounding_error:
        print "E: reduction(+:dsum)"
        result = False

    dsum = 0
    dpt = 0
    for i in xrange(0, 20):
        dpt *= dt
    ddiff = (1 - dpt) / (1 - dt)

    if 'omp parallel sections private(i) reduction(-:ddiff)':
        if 'omp section':
            for i in xrange(0,6):
                ddiff -= math.pow(dt, i)
        if 'omp section':
            for i in xrange(6,12):
                ddiff -= math.pow(dt, i)
        if 'omp section':
            for i in xrange(12,20):
                ddiff -= math.pow(dt, i)

    if abs(ddiff) > rounding_error:
        print "E: reduction(-:ddiff)"
        result = False

    if 'omp parallel sections private(i) reduction(*:product)':
        if 'omp section':
            for i in xrange(1,3):
                product *= i
        if 'omp section':
            for i in xrange(3,6):
                product *= i
        if 'omp section':
            for i in xrange(6,11):
                product *= i

    known_product = 3628800

    if known_product != product:
        print "E: reduction(*:product)"
        result = False

    logics = [1 for i in xrange(0,1000)]

    if 'omp parallel sections private(i) reduction(&&:logic_and)':
        if 'omp section':
            for i in xrange(0, 300):
                logic_and = (logic_and and logics[i])
        if 'omp section':
            for i in xrange(300, 700):
                logic_and = (logic_and and logics[i])
        if 'omp section':
            for i in xrange(700, 1000):
                logic_and = (logic_and and logics[i])

    if not logic_and:
        print "E: reduction(&&:logic_and)"
        result = False

    logic_and = 1;
    logics[1000/2]=0

    if 'omp parallel sections private(i) reduction(&&:logic_and)':
        if 'omp section':
            for i in xrange(0, 300):
                logic_and = (logic_and and logics[i])
        if 'omp section':
            for i in xrange(300, 700):
                logic_and = (logic_and and logics[i])
        if 'omp section':
            for i in xrange(700, 1000):
                logic_and = (logic_and and logics[i])

    if logic_and:
        print "E: reduction(&&:logic_and) with logics[1000/2]=0"
        result = False

    logics = [0 for i in xrange(0,1000)]

    if 'omp parallel sections private(i) reduction(||:logic_or)':
        if 'omp section':
            for i in xrange(0, 300):
                logic_or = (logic_or or logics[i])
        if 'omp section':
            for i in xrange(300, 700):
                logic_or = (logic_or or logics[i])
        if 'omp section':
            for i in xrange(700, 1000):
                logic_or = (logic_or or logics[i])

    if logic_or:
        print "E: reduction(||:logic_or)"
        result = False

    logic_or = 0;
    logics[1000/2]=1

    if 'omp parallel sections private(i) reduction(||:logic_or)':
        if 'omp section':
            for i in xrange(0, 300):
                logic_or = (logic_or or logics[i])
        if 'omp section':
            for i in xrange(300, 700):
                logic_or = (logic_or or logics[i])
        if 'omp section':
            for i in xrange(700, 1000):
                logic_or = (logic_or or logics[i])

    if not logic_or:
        print "E: reduction(||:logic_or) with logics[1000/2]=1"
        result = False

    logics = [1 for i in xrange(0,1000)]

    if 'omp parallel sections private(i) reduction(&:bit_and)':
        if 'omp section':
            for i in xrange(0, 300):
                bit_and = (bit_and & logics[i])
        if 'omp section':
            for i in xrange(300, 700):
                bit_and = (bit_and & logics[i])
        if 'omp section':
            for i in xrange(700, 1000):
                bit_and = (bit_and & logics[i])

    if not bit_and:
        print "E: reduction(&:bit_and)"
        result = False

    bit_and = 1;
    logics[1000/2]=0

    if 'omp parallel sections private(i) reduction(&:bit_and)':
        if 'omp section':
            for i in xrange(0, 300):
                bit_and = (bit_and & logics[i])
        if 'omp section':
            for i in xrange(300, 700):
                bit_and = (bit_and & logics[i])
        if 'omp section':
            for i in xrange(700, 1000):
                bit_and = (bit_and & logics[i])

    if bit_and:
        print "E: reduction(&:bit_and) with logics[1000/2]=0"
        result = False

    logics = [0 for i in xrange(0,1000)]

    if 'omp parallel sections private(i) reduction(|:bit_or)':
        if 'omp section':
            for i in xrange(0, 300):
                bit_or = (bit_or | logics[i])
        if 'omp section':
            for i in xrange(300, 700):
                bit_or = (bit_or | logics[i])
        if 'omp section':
            for i in xrange(700, 1000):
                bit_or = (bit_or | logics[i])

    if bit_or:
        print "E: reduction(|:bit_or)"
        result = False

    bit_or = 0;
    logics[1000/2]=1

    if 'omp parallel sections private(i) reduction(|:bit_or)':
        if 'omp section':
            for i in xrange(0, 300):
                bit_or = (bit_or | logics[i])
        if 'omp section':
            for i in xrange(300, 700):
                bit_or = (bit_or | logics[i])
        if 'omp section':
            for i in xrange(700, 1000):
                bit_or = (bit_or | logics[i])

    if not bit_or:
        print "E: reduction(|:bit_or) with logics[1000/2]=1"
        result = False

    logics = [0 for i in xrange(0,1000)]

    if 'omp parallel sections private(i) reduction(^:exclusiv_bit_or)':
        if 'omp section':
            for i in xrange(0, 300):
                exclusiv_bit_or = (exclusiv_bit_or ^ logics[i])
        if 'omp section':
            for i in xrange(300, 700):
                exclusiv_bit_or = (exclusiv_bit_or ^ logics[i])
        if 'omp section':
            for i in xrange(700, 1000):
                exclusiv_bit_or = (exclusiv_bit_or ^ logics[i])

    if exclusiv_bit_or:
        print "E: reduction(^:exclusiv_bit_or)"
        result = False

    exclusiv_bit_or = 0;
    logics[1000/2]=1

    if 'omp parallel sections private(i) reduction(^:exclusiv_bit_or)':
        if 'omp section':
            for i in xrange(0, 300):
                exclusiv_bit_or = (exclusiv_bit_or ^ logics[i])
        if 'omp section':
            for i in xrange(300, 700):
                exclusiv_bit_or = (exclusiv_bit_or ^ logics[i])
        if 'omp section':
            for i in xrange(700, 1000):
                exclusiv_bit_or = (exclusiv_bit_or ^ logics[i])

    if not exclusiv_bit_or:
        print "E: reduction(^:exclusiv_bit_or) with logics[1000/2]=1"
        result = False
    return result
