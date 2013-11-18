def omp_parallel_reduction(): 
    import math
    dt = 0.5
    rounding_error = 1.E-9

    sum = 0
    dsum = 0
    dt = 1. / 3.
    result = True
    product = 1
    logic_and = 1
    logic_or = 0
    bit_and = 1
    bit_or = 0
    exclusiv_bit_or = 0

    known_sum = (1000 * (1000 + 1)) / 2

    'omp parallel for schedule(dynamic,1) private(i) reduction(+:sum)'
    for i in xrange(1,1001):
        sum += i

    if known_sum != sum:
        print "E: reduction(+:sum)"
        result = False

    diff = (1000 * (1000 + 1)) / 2

    'omp parallel for schedule(dynamic,1) private(i) reduction(-:diff)'
    for i in xrange(1,1001):
        diff -= i

    if diff != 0:
        print "E: reduction(-:diff)"
        result = False

    dsum = 0
    dpt = 0
    for i in xrange(0, 20):
        dpt *= dt
    dknown_sum = (1 - dpt) / (1 - dt)

    'omp parallel for schedule(dynamic,1) private(i) reduction(+:dsum)'
    for i in xrange(0,20):
        dsum += math.pow(dt, i)

    if abs(dsum-dknown_sum) > rounding_error:
        print "E: reduction(+:dsum)"
        result = False

    dsum = 0
    dpt = 1
    for i in xrange(0, 20):
        dpt *= dt
    ddiff = (1 - dpt) / (1 - dt)

    'omp parallel for schedule(dynamic,1) private(i) reduction(-:ddiff)'
    for i in xrange(0,20):
        ddiff -= math.pow(dt, i)

    if abs(ddiff) > rounding_error:
        print "E: reduction(-:ddiff)"
        result = False

    'omp parallel for schedule(dynamic,1) private(i) reduction(*:product)'
    for i in xrange(1,11):
        product *= i

    known_product = 3628800

    if known_product != product:
        print "E: reduction(*:product)"
        result = False

    logics = [1 for i in xrange(0,1000)]

    'omp parallel for schedule(dynamic,1) private(i) reduction(&&:logic_and)'
    for i in xrange(0, 1000):
        logic_and = (logic_and and logics[i])

    if not logic_and:
        print "E: reduction(&&:logic_and)"
        result = False

    logic_and = 1;
    logics[1000/2]=0

    'omp parallel for schedule(dynamic,1) private(i) reduction(&&:logic_and)'
    for i in xrange(0, 1000):
        logic_and = (logic_and and logics[i])

    if logic_and:
        print "E: reduction(&&:logic_and) with logics[1000/2]=0"
        result = False

    logics = [0 for i in xrange(0,1000)]

    'omp parallel for schedule(dynamic,1) private(i) reduction(||:logic_or)'
    for i in xrange(0, 1000):
        logic_or = (logic_or or logics[i])

    if logic_or:
        print "E: reduction(||:logic_or)"
        result = False

    logic_or = 0;
    logics[1000/2]=1

    'omp parallel for schedule(dynamic,1) private(i) reduction(||:logic_or)'
    for i in xrange(0, 1000):
        logic_or = (logic_or or logics[i])

    if not logic_or:
        print "E: reduction(||:logic_or) with logics[1000/2]=1"
        result = False

    logics = [1 for i in xrange(0,1000)]

    'omp parallel for schedule(dynamic,1) private(i) reduction(&:bit_and)'
    for i in xrange(0, 1000):
        bit_and = (bit_and & logics[i])

    if not bit_and:
        print "E: reduction(&:bit_and)"
        result = False

    bit_and = 1;
    logics[1000/2]=0

    'omp parallel for schedule(dynamic,1) private(i) reduction(&:bit_and)'
    for i in xrange(0, 1000):
        bit_and = (bit_and & logics[i])

    if bit_and:
        print "E: reduction(&:bit_and) with logics[1000/2]=0"
        result = False

    logics = [0 for i in xrange(0,1000)]

    'omp parallel for schedule(dynamic,1) private(i) reduction(|:bit_or)'
    for i in xrange(0, 1000):
        bit_or = (bit_or | logics[i])

    if bit_or:
        print "E: reduction(|:bit_or)"
        result = False

    bit_or = 0;
    logics[1000/2]=1

    'omp parallel for schedule(dynamic,1) private(i) reduction(|:bit_or)'
    for i in xrange(0, 1000):
        bit_or = (bit_or | logics[i])

    if not bit_or:
        print "E: reduction(|:bit_or) with logics[1000/2]=1"
        result = False

    logics = [0 for i in xrange(0,1000)]

    'omp parallel for schedule(dynamic,1) private(i) reduction(^:exclusiv_bit_or)'
    for i in xrange(0, 1000):
        exclusiv_bit_or = (exclusiv_bit_or ^ logics[i])

    if exclusiv_bit_or:
        print "E: reduction(^:exclusiv_bit_or)"
        result = False

    exclusiv_bit_or = 0;
    logics[1000/2]=1

    'omp parallel for schedule(dynamic,1) private(i) reduction(^:exclusiv_bit_or)'
    for i in xrange(0, 1000):
        exclusiv_bit_or = (exclusiv_bit_or ^ logics[i])

    if not exclusiv_bit_or:
        print "E: reduction(^:exclusiv_bit_or) with logics[1000/2]=1"
        result = False
    return result
