def omp_for_reduction():
    DOUBLE_DIGITS = 20
    MAX_FACTOR = 10
    KNOWN_PRODUCT = 3628800
    rounding_error = 1.e-9
    result = 0
    LOOPCOUNT=1000
    logicsArray = [0]*LOOPCOUNT
    sum = 0
    product = 1
    known_sum = (LOOPCOUNT * (LOOPCOUNT + 1)) / 2
    dt = 1. / 3.
    dsum=0.
    logics = logicsArray
    logic_and = 1
    logic_or = 0
    bit_and = 1
    bit_or = 0
    exclusiv_bit_or = 0

    # testing integer addition
    'omp parallel for schedule(dynamic,1) reduction(+:sum)'
    for j in range(1, LOOPCOUNT+1):
        sum = sum + j
    if known_sum != sum:
        result+=1
        print 'Error in sum with integers'

    # testing integer substaction
    diff = (LOOPCOUNT * (LOOPCOUNT + 1)) / 2
    'omp parallel for schedule(dynamic,1) reduction(-:diff)'
    for j in range(1, LOOPCOUNT+1):
        diff = diff - j
    if diff != 0:
        result+=1
        print 'Error in difference with integers'

    # testing integer multiplication
    'omp parallel for schedule(dynamic,1) reduction(*:product)'
    for j in range(1, MAX_FACTOR +1):
        product *= j
    known_product = KNOWN_PRODUCT
    if known_product != product:
        result+=1
        print 'Error in product with integers'

    # testing bit and
    logics = [1] * LOOPCOUNT
    'omp parallel for schedule(dynamic,1) reduction(&:logic_and)'
    for logic in logics:
        logic_and = logic_and & logic
    if not logic_and:
        result+=1
        print 'Error in bit and part 1'

    logics[LOOPCOUNT/2]=0
    'omp parallel for schedule(dynamic,1) reduction(&:logic_and)'
    for logic in logics:
        logic_and = logic_and & logic
    if logic_and:
        result+=1
        print 'Error in bit and part 2'

    # testing bit or
    logics = [0] * LOOPCOUNT
    'omp parallel for schedule(dynamic,1) reduction(|:logic_or)'
    for logic in logics:
        logic_or = logic_or | logic
    if logic_or:
        result+=1
        print 'Error in logic or part 1'

    logics[LOOPCOUNT/2]=1
    'omp parallel for schedule(dynamic,1) reduction(|:logic_or)'
    for logic in logics:
        logic_or = logic_or | logic
    if not logic_or:
        result+=1
        print 'Error in logic or part 2'

    # testing exclusive bit or
    logics = [0] * LOOPCOUNT
    'omp parallel for schedule(dynamic,1) reduction(^:exclusiv_bit_or)'
    for logic in logics:
        exclusiv_bit_or = exclusiv_bit_or ^ logic
    if exclusiv_bit_or:
        result+=1
        print 'Error in exclusive bit or part 1'

    logics[LOOPCOUNT/2]=1
    'omp parallel for schedule(dynamic,1) reduction(^:exclusiv_bit_or)'
    for logic in logics:
        exclusiv_bit_or = exclusiv_bit_or ^ logic
    if not logic_or:
        result+=1
        print 'Error in exclusive bit or part 2'

    return result == 0
