#pythran export CROTG(complex, complex, float, complex)
#runas CROTG(complex(1,2),complex(5,6),3.4,complex(10,-3))
import math

def CROTG(CA,CB,C=0,S=0):
#     .. Scalar Arguments ..
#      COMPLEX CA,CB,S
#      REAL C
#     ..
#
#  Purpose
#  =======
#
#  CROTG determines a complex Givens rotation.
#
#  =====================================================================
#
#     .. Local Scalars ..
#      COMPLEX ALPHA
#      REAL NORM,SCALE
#     ..
    if (abs(CA) == 0.):
        C = 0.
        S = complex(1.,0.)
        CA = CB
    else:
        SCALE = abs(CA) + abs(CB)
        NORM = SCALE*math.sqrt((abs(CA/SCALE))**2+ (abs(CB/SCALE))**2)
        ALPHA = CA/abs(CA)
        C = abs(CA)/NORM
        S = ALPHA*(CB.conjugate())/NORM
        CA = ALPHA*NORM
    return (CA,CB,C,S)



