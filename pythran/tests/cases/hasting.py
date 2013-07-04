#from http://wiki.scipy.org/Cookbook/Theoretical_Ecology/Hastings_and_Powell
#pythran export fweb(float [], float, float, float, float, float, float, float)
import numpy as np
def fweb(y, t, a1, a2, b1, b2, d1, d2):
    yprime = np.empty((3,))
    yprime[0] = y[0] * (1. - y[0]) - a1*y[0]*y[1]/(1. + b1 * y[0])
    yprime[1] = a1*y[0]*y[1] / (1. + b1 * y[0]) - a2 * y[1]*y[2] / (1. + b2 * y[1]) - d1 * y[1]
    yprime[2] = a2*y[1]*y[2]/(1. + b2*y[1]) - d2*y[2]
    return yprime
