#pythran export whetstone(int)
#runas whetstone(2*10**2)
#bench whetstone(1500)
"""
/*
 * C Converted Whetstone Double Precision Benchmark
 *        Version 1.2    22 March 1998
 *
 *    (c) Copyright 1998 Painter Engineering, Inc.
 *        All Rights Reserved.
 *
 *        Permission is granted to use, duplicate, and
 *        publish this text and program as long as it
 *        includes this entire comment block and limited
 *        rights reference.
 *
 * Converted by Rich Painter, Painter Engineering, Inc. based on the
 * www.netlib.org benchmark/whetstoned version obtained 16 March 1998.
 *
 * A novel approach was used here to keep the look and feel of the
 * FORTRAN version.  Altering the FORTRAN-based array indices,
 * starting at element 1, to start at element 0 for C, would require
 * numerous changes, including decrementing the variable indices by 1.
 * Instead, the array E1[] was declared 1 element larger in C.  This
 * allows the FORTRAN index range to function without any literal or
 * variable indices changes.  The array element E1[0] is simply never
 * used and does not alter the benchmark results.
 *
 * The major FORTRAN comment blocks were retained to minimize
 * differences between versions.  Modules N5 and N12, like in the
 * FORTRAN version, have been eliminated here.
 *
 * An optional command-line argument has been provided [-c] to
 * offer continuous repetition of the entire benchmark.
 * An optional argument for setting an alternate LOOP count is also
 * provided.  Define PRINTOUT to cause the POUT() function to print
 * outputs at various stages.  Final timing measurements should be
 * made with the PRINTOUT undefined.
 *
 * Questions and comments may be directed to the author at
 *            r.painter@ieee.org
 */
"""
from math import sin as DSIN, cos as DCOS, atan as DATAN, log as DLOG, exp as DEXP, sqrt as DSQRT


def whetstone(loopstart):

#    The actual benchmark starts here.
    T  = .499975;
    T1 = 0.50025;
    T2 = 2.0;

#    With loopcount LOOP=10, one million Whetstone instructions
#    will be executed in EACH MAJOR LOOP..A MAJOR LOOP IS EXECUTED
#    'II' TIMES TO INCREASE WALL-CLOCK TIMING ACCURACY.
    LOOP = loopstart;
    II   = 1;

    JJ = 1;

    while JJ <= II:

        N1  = 0;
        N2  = 12 * LOOP;
        N3  = 14 * LOOP;
        N4  = 345 * LOOP;
        N6  = 210 * LOOP;
        N7  = 32 * LOOP;
        N8  = 899 * LOOP;
        N9  = 616 * LOOP;
        N10 = 0;
        N11 = 93 * LOOP;
    #    Module 1: Simple identifiers
        X1  =  1.0;
        X2  = -1.0;
        X3  = -1.0;
        X4  = -1.0;

        for I in xrange(1,N1+1):
            X1 = (X1 + X2 + X3 - X4) * T;
            X2 = (X1 + X2 - X3 + X4) * T;
            X3 = (X1 - X2 + X3 + X4) * T;
            X4 = (-X1+ X2 + X3 + X4) * T;

    #    Module 2: Array elements
        E1 =  [ 1.0, -1.0, -1.0, -1.0 ]

        for I in xrange(1,N2+1):
            E1[0] = ( E1[0] + E1[1] + E1[2] - E1[3]) * T;
            E1[1] = ( E1[0] + E1[1] - E1[2] + E1[3]) * T;
            E1[2] = ( E1[0] - E1[1] + E1[2] + E1[3]) * T;
            E1[3] = (-E1[0] + E1[1] + E1[2] + E1[3]) * T;


    #    Module 3: Array as parameter
        for I in xrange(1,N3+1):
            PA(E1, T, T2);


    #    Module 4: Conditional jumps
        J = 1;
        for I in xrange(1,N4+1):
            if J == 1:
                J = 2;
            else:
                J = 3;

            if J > 2:
                J = 0;
            else:
                J = 1;

            if J < 1:
                J = 1;
            else:
                J = 0;


    #    Module 5: Omitted
    #     Module 6: Integer arithmetic

        J = 1;
        K = 2;
        L = 3;

        for I in xrange(1,N6+1):
            J = J * (K-J) * (L-K);
            K = L * K - (L-J) * K;
            L = (L-K) * (K+J);
            E1[L-2] = J + K + L;
            E1[K-2] = J * K * L;


    #    Module 7: Trigonometric functions
        X = 0.5;
        Y = 0.5;

        for I in xrange(1,N7+1):
            X = T * DATAN(T2*DSIN(X)*DCOS(X)/(DCOS(X+Y)+DCOS(X-Y)-1.0));
            Y = T * DATAN(T2*DSIN(Y)*DCOS(Y)/(DCOS(X+Y)+DCOS(X-Y)-1.0));


    #    Module 8: Procedure calls
        X = 1.0;
        Y = 1.0;
        Z = 1.0;

        for I in xrange(1,N8+1):
            Z=P3(X,Y,T, T2)

    #    Module 9: Array references
        J = 1;
        K = 2;
        L = 3;
        E1[0] = 1.0;
        E1[1] = 2.0;
        E1[2] = 3.0;

        for I in xrange(1,N9+1):
            P0(E1, J, K, L)


    #    Module 10: Integer arithmetic
        J = 2;
        K = 3;

        for I in xrange(1,N10+1):
            J = J + K;
            K = J + K;
            J = K - J;
            K = K - J - J;


    #    Module 11: Standard functions
        X = 0.75;

        for I in xrange(1,N11+1):
            X = DSQRT(DEXP(DLOG(X)/T1));

        JJ+=1


    KIP = (100.0*LOOP*II)
    return KIP

def PA(E, T, T2):
    J = 0;

    while J<6:
        E[0] = ( E[0] + E[1] + E[2] - E[3]) * T;
        E[1] = ( E[0] + E[1] - E[2] + E[3]) * T;
        E[2] = ( E[0] - E[1] + E[2] + E[3]) * T;
        E[3] = (-E[0] + E[1] + E[2] + E[3]) / T2;
        J += 1;

def P0(E1, J, K, L):
    E1[J-1] = E1[K-1];
    E1[K-1] = E1[L-1];
    E1[L-1] = E1[J-1];

def P3(X, Y, T, T2):
    X1 = X;
    Y1 = Y;
    X1 = T * (X1 + Y1);
    Y1 = T * (X1 + Y1);
    return (X1 + Y1) / T2;

