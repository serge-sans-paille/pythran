#pythran export ln(float64[], float64[])
#runas import numpy; a = numpy.arange(0, 1., 1./100); b = numpy.empty_like(a) ; ln(a,b)
def ln(X, Y):
    Y[:] = (X-1) - (X-1)**2 / 2 + (X-1)**3 / 3 - (X-1)**4 / 4 + (X-1)**5 / 5 - (X-1)**6 / 6 + (X-1)**7 / 7 - (X-1)**8 / 8 + (X-1)**9 / 9
    return Y

