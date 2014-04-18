#pythran export fft(complex [])
#runas from numpy import ones ; a = ones(2**10, dtype=complex) ; fft(a)
#bench from numpy import ones ; a = ones(2**14, dtype=complex) ; fft(a)

import math, numpy as np

def fft(x):
   N = x.shape[0]
   if N == 1:
       return np.array(x)
   e=fft(x[::2])
   o=fft(x[1::2])
   M=N//2
   l=[ e[k] + o[k]*math.e**(-2j*math.pi*k/N) for k in xrange(M) ]
   r=[ e[k] - o[k]*math.e**(-2j*math.pi*k/N) for k in xrange(M) ]
   return np.array(l+r)

