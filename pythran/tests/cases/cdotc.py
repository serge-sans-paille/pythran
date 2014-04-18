#pythran export CDOTC(int, complex list, int, complex list, int)
#runas CDOTC(2,[complex(1,2),complex(2,3),complex(3,4),complex(5,6)],2,[complex(3,4),complex(1,2),complex(2,3),complex(5,6)],3)
#bench sz = 20000000; in1 = map(complex, xrange(sz), xrange(sz)); in2 = map(complex, xrange(sz), xrange(sz));CDOTC(sz / 6,in1,2,in2,3)
def CDOTC(N,CX,INCX,CY,INCY):
#     .. Scalar Arguments ..
#      INTEGER INCX,INCY,N
#     ..
#     .. Array Arguments ..
#      COMPLEX CX(#),CY(#)
#     ..
#
#  Purpose
#  =======
#
#     forms the dot product of two vectors, conjugating the first
#     vector.
#
#  Further Details
#  ===============
#
#     jack dongarra, linpack,  3/11/78.
#     modified 12/3/93, array(1) declarations changed to array(#)
#
#  =====================================================================
#
    CTEMP = complex(0.0,0.0)
    CDOTC = complex(0.0,0.0)
    if (N <= 0):
        return
    if (INCX == 1 and  INCY == 1):

#
#        code for both increments equal to 1
#
        for I in range(N):
            CTEMP = CTEMP + (CX[I].conjugate())*CY[I]
    else:
#
#        code for unequal increments or equal increments
#          not equal to 1
#
        IX = 0
        IY = 0
        if (INCX < 0):
            IX = (-N+1)*INCX
        if (INCY < 0):
            IY = (-N+1)*INCY
        for I in range(N):
            CTEMP = CTEMP + (CX[IX].conjugate())*CY[IY]
            IX = IX + INCX
            IY = IY + INCY
    return CTEMP

