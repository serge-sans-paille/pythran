# Authors: Stefan van der Walt, Nathan Faggian, Aron Ahmadia
# https://github.com/stefanv/growcut_py
from __future__ import division
 
import numpy as np
cimport cython
from libcpp.vector cimport vector
 
cdef extern from "math.h" nogil:
    double sqrt(double)
    double exp(double)
    double log(double)

 

@cython.boundscheck(False)
@cython.wraparound(False)
def BlackScholes(vector[double] stock_price, vector[double] option_strike, vector[double] option_years, double Riskfree,  double Volatility, int nb_opt):
    cdef:
        double RSQRT2PI = 1 / sqrt(np.pi * 2)
        double A1 = 0.31938153
        double A2 = -0.356563782
        double A3 = 1.781477937
        double A4 = -1.821255978
        double A5 = 1.330274429
        double sqrtT, d1, D2, K, CNDD1, CNDD2, expRT
        vector[int] call_result, put_result
    for opt in xrange(0, nb_opt) :
        sqrtT = sqrt(option_years[opt])
        d1 = log(stock_price[opt] / option_strike[opt])
        d1 += (Riskfree + 0.5 * Volatility * Volatility) * option_years[opt]
        d1 /= (Volatility * sqrtT)
        d2 = d1 - Volatility * sqrtT
        K = 1.0 / (1.0 + 0.2316419 * abs(d1))
        CNDD1 = RSQRT2PI * exp(-0.5 * d1 * d1) * (K * (A1 + K * (A2 + K * (A3 + K * (A4 + K * A5)))))
        K = 1.0 / (1.0 + 0.2316419 * abs(d2))
        CNDD2 = RSQRT2PI * exp(-0.5 * d2 * d2) * (K * (A1 + K * (A2 + K * (A3 + K * (A4 + K * A5)))))
        expRT = exp(-Riskfree * option_years[opt])
        call_result.append(stock_price[opt] * CNDD1 - option_strike[opt] * expRT * CNDD2)
        put_result.append(option_strike[opt] * expRT * (1.0 - CNDD2) - stock_price[opt] * (1.0 - CNDD1))
    return call_result, put_result

