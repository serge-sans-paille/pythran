#pythran export ep()
import math

def ep():
#    classe = 'S'
#    M = 24
#    classe = 'W'
#    M = 25
    classe = 'A'
    M = 28
#    classe = 'B'
#    M = 30
#    classe = 'C'
#    M = 32
    NQ = 10
    MK = 16
    MM = M-MK
    NK = 1 << MK
    NN = 1 << MM
    EPSILON = 1.0e-8
    A = 1220703125.0
    S = 271828183.0
    q = [0.]*NQ
    dum = [1.,1.,1.]
    "omp threadprivate(x)"
    x = [0.]*2*NK;
    nthreads = 1
    print("\n\n NAS Parallel Benchmarks 2.3 OpenMP C version - EP Benchmark\n")
    size = pow(2.0, M+1)
    print " Number of random numbers generated:", size, "s"
    verified = False
    np = NN

#should not be remove as dead code ....
    dum[0] = vranlc(0, dum[0], dum[1], dum, 2)
    dum[0],dum[1] = randlc(dum[1], dum[2])
    x = [-1.0e99 for i in xrange(0,2*NK) ]
    Mops = math.log(math.sqrt(abs(max(1.0, 1.0))));

    t1 = 0.
    t1 = vranlc(0, t1, A, x, 0);

    t1 = A

    for i in xrange(1, MK+2):
        t2,t1 = randlc(t1, t1)

    an = t1
    tt = S
    gc = 0.0
    sx = 0.0
    sy = 0.0
    
    for i in xrange(NQ):
        q[i] = 0.0

    k_offset = -1;

    "omp parallel copyin(x)"
    if True:
        t1 = t2 = t3 = t4 = x1 = x2 =0.
        kk = i = ik = l = 0
        qq = [0.]*NQ

        "omp for reduction(+:sx,sy) schedule(static) private(k)"
        for k in xrange(1, np+1):
            kk = k_offset + k
            t1 = S
            t2 = an

            for i in xrange(1, 101):
                ik = kk / 2
                if 2 * ik != kk:
                    t3, t1 = randlc(t1, t2)
                if ik == 0:
                    break
                t3, t2 = randlc(t2, t2)
                kk = ik

            t1 = vranlc(2*NK, t1, A, x, -1)

            for i in xrange(0,NK):
                x1 = 2.0 * x[2*i] - 1.0
                x2 = 2.0 * x[2*i+1] - 1.0
                t1 = x1**2 + x2**2
                if t1 <= 1.0:
                    t2 = math.sqrt(-2.0 * math.log(t1) / t1)
                    t3 = x1 * t2
                    t4 = x2 * t2
                    l = int(max(abs(t3), abs(t4)))
                    qq[l] += 1.0
                    sx = sx + t3
                    sy = sy + t4


        "omp critical"
        for i in xrange(0,NQ):
            q[i] += qq[i]

    for i in xrange(0,NQ):
        gc = gc + q[i]

    nit = 0
    if M == 24:
        if abs((sx- (-3.247834652034740e3))/sx) <= EPSILON and abs((sy- (-6.958407078382297e3))/sy) <= EPSILON:
            verified = True
    elif M == 25:
        if abs((sx- (-2.863319731645753e3))/sx) <= EPSILON and abs((sy- (-6.320053679109499e3))/sy) <= EPSILON:
            verified = True
    elif M == 28:
        if abs((sx- (-4.295875165629892e3))/sx) <= EPSILON and abs((sy- (-1.580732573678431e4))/sy) <= EPSILON:
            verified = True
    elif M == 30:
        if abs((sx- (4.033815542441498e4))/sx) <= EPSILON and abs((sy- (-2.660669192809235e4))/sy) <= EPSILON:
            verified = True
    elif M == 32:
        if abs((sx- (4.764367927995374e4))/sx) <= EPSILON and abs((sy- (-8.084072988043731e4))/sy) <= EPSILON:
            verified = True

    print "EP Benchmark Results:"
    print "N = 2^", M
    print "No. Gaussian Pairs =", gc
    print "Sums =", sx, sy
    print "Counts:"
    for i in xrange(0,NQ):
        print i, q[i]

def vranlc(n, x_seed, a, y, offset):
    r23 = pow(0.5, 23.0)
    r46 = (r23*r23)
    t23 = pow(2.0, 23.0)
    t46 = (t23*t23)
    t1 = r23 * a
    a1 = int(t1);
    a2 = a - t23 * a1
    x = x_seed
    for i in xrange(1,n+1):
        t1 = r23 * x
        x1 = int(t1)
        x2 = x - t23 * x1
        t1 = a1 * x2 + a2 * x1
        t2 = int(r23 * t1)
        z = t1 - t23 * t2;
        t3 = t23 * z + a2 * x2;
        t4 = int(r46 * t3);
        x = t3 - t46 * t4;
        y[i+offset] = r46 * x
    return x

def randlc (x, a):
    r23=pow(0.5, 23.0)
    r46=(r23*r23)
    t23=(2.0*2.0*2.0*2.0*2.0*2.0*2.0*2.0*2.0*2.0*2.0*2.0*2.0*2.0*2.0*2.0*2.0*2.0*2.0*2.0*2.0*2.0*2.0)
    t46=(t23*t23)
    t1 = r23 * a
    a1 = int(t1)
    a2 = a - t23 * a1
    t1 = r23 * x
    x1 = int(t1)
    x2 = x - t23 * x1
    t1 = a1 * x2 + a2 * x1
    t2 = int(r23 * t1)
    z = t1 - t23 * t2
    t3 = t23 * z + a2 * x2
    t4 = int(r46 * t3)
    x = t3 - t46 * t4;
    return (r46 * x,x);

