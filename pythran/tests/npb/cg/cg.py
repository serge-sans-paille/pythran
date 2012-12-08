#pythran export cg(str)
import math


def cg(classe):
    """classe value can be S/W/A/B/C"""
    RCOND = 1.0e-1
    if classe == "S":
        NA = 1400
        NONZER = 7
        NITER = 15
        SHIFT = 10.0
        zeta_verify_value = 8.5971775078648
    elif classe == "W":
        NA = 7000
        NONZER = 8
        NITER = 15
        SHIFT = 12.0
        zeta_verify_value = 10.362595087124
    elif classe == "A":
        NA = 14000
        NONZER = 11
        NITER = 15
        SHIFT = 20.0
        zeta_verify_value = 17.130235054029
    elif classe == "B":
        NA = 75000
        NONZER = 13
        NITER = 75
        SHIFT = 60.0
        zeta_verify_value = 22.712745482631
    elif classe == "C":
        NA = 150000
        NONZER = 15
        NITER = 75
        SHIFT = 110.0
        zeta_verify_value = 28.973605592845
    else:
        classe = 'U'
    NZ = NA * (NONZER + 1) * (NONZER + 1) + NA * (NONZER + 2)

    colidx = [0] * (NZ + 1)
    rowstr = [0] * (NA + 2)
    iv = [0] * (2 * NA + 2)
    arow = [0] * (NZ + 1)
    acol = [0] * (NZ + 1)

    v = [0] * (NA + 2)
    aelt = [0] * (NZ + 1)
    a = [0] * (NZ + 1)
    x = [0] * (NA + 3)
    z = [0] * (NA + 3)
    p = [0] * (NA + 3)
    q = [0] * (NA + 3)
    r = [0] * (NA + 3)
    w = [0] * (NA + 3)

    nthreads = 1
    firstrow = 1
    lastrow = NA
    firstcol = 1
    lastcol = NA
    print "\n\n NAS Parallel Benchmarks 2.3 OpenMP C version - CG Benchmark\n"
    print " Size: ", NA, "\n"
    print " Iterations: ", NITER, "\n"

    naa = NA
    nzz = NZ

    tran = 314159265.0
    amult = 1220703125.0
    zeta, tran = randlc(tran, amult)

    tran = makea(naa, nzz, a, colidx, rowstr, NONZER,
      firstrow, lastrow, firstcol, lastcol,
      RCOND, arow, acol, aelt, v, iv, SHIFT, tran, amult)

    "omp parallel private(it,i,j,k)"
    if True:
        "omp for nowait"
        for j in xrange(1, lastrow - firstrow + 2):
            for k in xrange(rowstr[j], rowstr[j + 1]):
                colidx[k] = colidx[k] - firstcol + 1

        "omp for nowait"
        for i in xrange(1, NA + 2):
            x[i] = 1.0

        "omp single"
        zeta = 0.0

        for it in xrange(1, 2):
            rnorm = conj_grad(colidx, rowstr, x, z, a, p, q, r,
                w, naa, lastcol, firstcol, lastrow, firstrow)
            "omp single"
            if True:
                norm_temp11 = 0.0
                norm_temp12 = 0.0

            "omp for reduction( + : norm_temp11, norm_temp12)"
            for j in xrange(1, lastcol - firstcol + 2):
                norm_temp11 = norm_temp11 + x[j] * z[j]
                norm_temp12 = norm_temp12 + z[j] * z[j]

            "omp single"
            norm_temp12 = 1.0 / math.sqrt(norm_temp12)

            "omp for"
            for j in xrange(1, lastcol - firstcol + 2):
                x[j] = norm_temp12 * z[j]

        "omp for nowait"
        for i in xrange(1, NA + 2):
            x[i] = 1.0

        "omp single"
        zeta = 0.0

    "omp parallel private(it, i, j, k)"
    for it in xrange(1, NITER + 1):
        rnorm = conj_grad(colidx, rowstr, x, z, a, p, q, r,
            w, naa, lastcol, firstcol, lastrow, firstrow)
        "omp single"
        if True:
            norm_temp11 = 0.0
            norm_temp12 = 0.0

        "omp for reduction( + : norm_temp11, norm_temp12)"
        for j in xrange(1, lastcol - firstcol + 2):
            norm_temp11 = norm_temp11 + x[j] * z[j]
            norm_temp12 = norm_temp12 + z[j] * z[j]

        "omp single"
        if True:
            norm_temp12 = 1.0 / math.sqrt(norm_temp12)
            zeta = SHIFT + 1.0 / norm_temp11

        "omp master"
        if True:
            if it == 1:
                print "   iteration           ||r||                 zeta\n"
            print "    ", it, "       ", rnorm, zeta, "\n"

        "omp for"
        for j in xrange(1, lastcol - firstcol + 2):
            x[j] = norm_temp12 * z[j]

    print " Benchmark completed\n"

    epsilon = 1.0e-10
    if classe != 'U':
        if abs(zeta - zeta_verify_value) <= epsilon:
            verified = True
            print " VERIFICATION SUCCESSFUL\n"
            print " Zeta is    ", zeta, "\n"
            print " Error is   ", (zeta - zeta_verify_value), "\n"
        else:
            verified = False
            print " VERIFICATION FAILED\n"
            print " Zeta                ", zeta, "\n"
            print " The correct zeta is ", zeta_verify_value, "\n"
    else:
        verified = False
        print " Problem size unknown\n"
        print " NO VERIFICATION PERFORMED\n"


def makea(n, nz, a, colidx, rowstr, nonzer, firstrow, lastrow,
                firstcol, lastcol, rcond, arow, acol, aelt, v,
                iv, shift, tran, amult):
    size = 1.0
    ratio = math.pow(rcond, (1.0 / float(n)))
    nnza = 0

    "omp parallel for"
    for i in xrange(1, n + 1):
        colidx[n + i] = 0

    for iouter in xrange(1, n + 1):
        nzv = nonzer
        tran = sprnvc(n, nzv, v, iv, colidx, n, tran, amult)
        nzv = vecset(n, v, iv, nzv, iouter, 0.5)
        for ivelt in xrange(1, nzv + 1):
            jcol = iv[ivelt]
            if (jcol >= firstcol and jcol <= lastcol):
                scale = size * v[ivelt]
                for ivelt1 in xrange(1, nzv+1):
                    irow = iv[ivelt1]
                    if (irow >= firstrow and irow <= lastrow):
                        nnza = nnza + 1
                        if (nnza > nz):
                            print "Space for matrix exceeded in makea\n"
                            print "nnza, nzmax = ", nnza, ", ", nz, "\n"
                            print "iouter = ", iouter, "\n"
                            print "ERROR"
                        acol[nnza] = jcol
                        arow[nnza] = irow
                        aelt[nnza] = v[ivelt1] * scale
        size = size * ratio

    for i in xrange(firstrow, lastrow + 1):
        if (i >= firstcol and i <= lastcol):
            iouter = n + i
            nnza = nnza + 1
            if (nnza > nz):
                print "Space for matrix elements exceeded in makea\n"
                print "nnza, nzmax = ", nnza, ", ", nz, "\n"
                print "iouter = ", iouter, "\n"
                print "ERROR"
            acol[nnza] = i
            arow[nnza] = i
            aelt[nnza] = rcond - shift

    sparse(a, colidx, rowstr, n, arow, acol, aelt,
        firstrow, lastrow, v, iv, n, nnza)
    return tran


def sparse(a, colidx, rowstr, n, arow, acol, aelt, firstrow,
    lastrow, x, mark, offset, nnza):
    nrows = lastrow - firstrow + 1
    "omp parallel for"
    for j in xrange(1, n + 1):
        rowstr[j] = 0
        mark[j] = False

    rowstr[n + 1] = 0

    for nza in xrange(1, nnza + 1):
        j = (arow[nza] - firstrow + 1) + 1
        rowstr[j] = rowstr[j] + 1

    rowstr[1] = 1
    for j in xrange(2, nrows + 2):
        rowstr[j] = rowstr[j] + rowstr[j - 1]

    for nza in xrange(1, nnza + 1):
        j = arow[nza] - firstrow + 1
        k = rowstr[j]
        a[k] = aelt[nza]
        colidx[k] = acol[nza]
        rowstr[j] = rowstr[j] + 1

    for j in xrange(nrows, 0, -1):
        rowstr[j + 1] = rowstr[j]

    rowstr[1] = 1

    nza = 0
    "omp parallel for"
    for i in xrange(1, n + 1):
        x[i] = 0.0
        mark[i] = False

    jajp1 = rowstr[1]
    for j in xrange(1, nrows + 1):
        nzrow = 0
        for k in xrange(jajp1, rowstr[j + 1]):
            i = colidx[k]
            x[i] = x[i] + a[k]
            if (mark[i] == False and x[i] != 0.0):
                mark[i] = True
                nzrow = nzrow + 1
                mark[nzrow + offset] = i
        for k in xrange(1, nzrow + 1):
            i = mark[k + offset]
            mark[i] = False
            xi = x[i]
            x[i] = 0.0
            if (xi != 0.0):
                nza = nza + 1
                a[nza] = xi
                colidx[nza] = i
        jajp1 = rowstr[j + 1]
        rowstr[j + 1] = nza + rowstr[1]


def vecset(n, v, iv, nzv, i, val):
    set = False
    for k in xrange(1, nzv + 1):
        if iv[k] == i:
            v[k] = val
            set = True
    if set == False:
        nzv = nzv + 1
        v[nzv] = val
        iv[nzv] = i
    return nzv


def sprnvc(n, nz, v, iv, nzloc, offset, tran, amult):
    nzv = 0
    nzrow = 0
    nn1 = 2
    while nn1 < n:
        nn1 = 2 * nn1

    while nzv < nz:
        vecelt, tran = randlc(tran, amult)
        vecloc, tran = randlc(tran, amult)
        i = icnvrt(vecloc, nn1) + 1
        if i > n:
            continue

        if nzloc[i + offset] == 0:
            nzloc[i + offset] = 1
            nzrow = nzrow + 1
            nzloc[nzrow] = i
            nzv = nzv + 1
            v[nzv] = vecelt
            iv[nzv] = i

    for ii in xrange(1, nzrow + 1):
        i = nzloc[ii]
        nzloc[i + offset] = 0
    return tran


def icnvrt(x, ipwr2):
    return int(ipwr2 * x)


def vranlc(n, x_seed, a, y, offset):
    r23 = pow(0.5, 23.0)
    r46 = (r23 * r23)
    t23 = pow(2.0, 23.0)
    t46 = (t23 * t23)
    t1 = r23 * a
    a1 = int(t1)
    a2 = a - t23 * a1
    x = x_seed
    for i in xrange(1, n + 1):
        t1 = r23 * x
        x1 = int(t1)
        x2 = x - t23 * x1
        t1 = a1 * x2 + a2 * x1
        t2 = int(r23 * t1)
        z = t1 - t23 * t2
        t3 = t23 * z + a2 * x2
        t4 = int(r46 * t3)
        x = t3 - t46 * t4
        y[i + offset] = r46 * x
    return x


def randlc(x, a):
    r23 = pow(0.5, 23.0)
    r46 = (r23 * r23)
    t23 = pow(2.0, 23.0)
    t46 = (t23 * t23)
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
    x = t3 - t46 * t4
    return (r46 * x, x)


def conj_grad(colidx, rowstr, x, z, a, p, q, r, w, naa,
    lastcol, firstcol, lastrow, firstrow):
    cgitmax = 25

    "omp single nowait"
    rho = 0.0

    "omp for nowait"
    for j in xrange(1, naa + 2):
        q[j] = 0.0
        z[j] = 0.0
        r[j] = x[j]
        p[j] = r[j]
        w[j] = 0.0

    "omp for reduction( + : rho)"
    for j in xrange(1, lastcol - firstcol + 2):
        rho = rho + x[j] * x[j]

    for cgit in xrange(1, cgitmax + 1):
        "omp single nowait"
        if True:
            rho0 = rho
            d = 0.0
            rho = 0.0

        "omp for private(sum, k)"
        for j in xrange(1, lastrow - firstrow + 2):
            sum = 0.0
            for k in xrange(rowstr[j], rowstr[j + 1]):
                sum = sum + a[k] * p[colidx[k]]
            w[j] = sum

# unrolled-by-two version
#pragma omp for private(i,k)
#        for (j = 1; j <= lastrow-firstrow+1; j++) {
#        int iresidue;
#        double sum1, sum2;
#        i = rowstr[j];
#            iresidue = (rowstr[j+1]-i) % 2;
#            sum1 = 0.0;
#            sum2 = 0.0;
#            if (iresidue == 1) sum1 = sum1 + a[i]*p[colidx[i]];
#        for (k = i+iresidue; k <= rowstr[j+1]-2; k += 2) {
#        sum1 = sum1 + a[k]   * p[colidx[k]];
#        sum2 = sum2 + a[k+1] * p[colidx[k+1]];
#        }
#            w[j] = sum1 + sum2;
#        }
#*/
#/* unrolled-by-8 version
#pragma omp for private(i,k,sum)
#        for (j = 1; j <= lastrow-firstrow+1; j++) {
#        int iresidue;
#            i = rowstr[j];
#            iresidue = (rowstr[j+1]-i) % 8;
#            sum = 0.0;
#            for (k = i; k <= i+iresidue-1; k++) {
#                sum = sum +  a[k] * p[colidx[k]];
#            }
#            for (k = i+iresidue; k <= rowstr[j+1]-8; k += 8) {
#                sum = sum + a[k  ] * p[colidx[k  ]]
#                          + a[k+1] * p[colidx[k+1]]
#                          + a[k+2] * p[colidx[k+2]]
#                          + a[k+3] * p[colidx[k+3]]
#                          + a[k+4] * p[colidx[k+4]]
#                          + a[k+5] * p[colidx[k+5]]
#                          + a[k+6] * p[colidx[k+6]]
#                          + a[k+7] * p[colidx[k+7]];
#            }
#            w[j] = sum;
#        }
#*/

        "omp for"
        for j in xrange(1, lastcol - firstcol + 2):
            q[j] = w[j]

        "omp for nowait"
        for j in xrange(1, lastcol - firstcol + 2):
            w[j] = 0.0

        "omp for reduction( + : d)"
        for j in xrange(1, lastcol - firstcol + 2):
            d = d + p[j] * q[j]

        "omp single"
        alpha = rho0 / d

        "omp for"
        for j in xrange(1, lastcol - firstcol + 2):
            z[j] = z[j] + alpha * p[j]
            r[j] = r[j] - alpha * q[j]

        "omp for reduction( + : rho)"
        for j in xrange(1, lastcol - firstcol + 2):
            rho = rho + r[j] * r[j]


        "omp single"
        beta = rho / rho0

        "omp for"
        for j in xrange(1, lastcol - firstcol + 2):
            p[j] = r[j] + beta * p[j]

    "omp single nowait"
    sum = 0.0

    "omp for private(d, k)"
    for j in xrange(1, lastrow - firstrow + 2):
        d = 0.0
        for k in xrange(rowstr[j], rowstr[j + 1]):
            d = d + a[k] * z[colidx[k]]
        w[j] = d

    "omp for"
    for j in xrange(1, lastcol - firstcol + 2):
        r[j] = w[j]

    "omp for reduction( + : sum) private(d)"
    for j in xrange(1, lastcol - firstcol + 2):
        d = x[j] - r[j]
        sum = sum + d * d

    return math.sqrt(sum)
