#pythran export CCOPY(int, complex list, int, complex list, int)
#runas CCOPY(2,[complex(1,2),complex(2,3),complex(3,4),complex(5,6)],2,[complex(3,4),complex(1,2),complex(2,3),complex(5,6)],3)
#bench sz = 20000000; in1 = map(complex, xrange(sz), xrange(sz)); in2 = map(complex, xrange(sz), xrange(sz));CCOPY(sz / 6,in1,2,in2,3)
def CCOPY(N,CX,INCX,CY,INCY):
#  Purpose
#  =======
#
#     CCOPY copies a vector x to a vector y.
#
#  Further Details
#  ===============
#
#
#  =====================================================================
#
      	if N <= 0:
		return
      	if (INCX==1 and INCY==1):
#
#        code for both increments equal to 1
#
		for I in range(N):
			CY[I] = CX[I]
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
			CY[IY] = CX[IX]
	            	IX = IX + INCX
        	    	IY = IY + INCY
	return
