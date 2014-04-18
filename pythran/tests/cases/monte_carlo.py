# http://code.activestate.com/recipes/577263-numerical-integration-using-monte-carlo-method/
# Numerical Integration using Monte Carlo method
# FB - 201006137
#pythran export montecarlo_integration(float, float, int, float list, int)
#runas montecarlo_integration(1.,10.,100,[x/100. for x in range(100)],100)
#bench montecarlo_integration(1.,10.,650000,[x/100. for x in range(100)],100)
import math


def montecarlo_integration(xmin, xmax, numSteps,rand,randsize):
    # define any function here!
    def f(x):
        return math.sin(x)

    # find ymin-ymax
    ymin = f(xmin)
    ymax = ymin
    for i in xrange(numSteps):
        x = xmin + (xmax - xmin) * float(i) / numSteps
        y = f(x)
        if y < ymin: ymin = y
        if y > ymax: ymax = y

    # Monte Carlo
    rectArea = (xmax - xmin) * (ymax - ymin)
    numPoints = numSteps # bigger the better but slower!
    ctr = 0
    for j in xrange(numPoints):
        x = xmin + (xmax - xmin) * rand[j%randsize]
        y = ymin + (ymax - ymin) * rand[j%randsize]
        if math.fabs(y) <= math.fabs(f(x)):
            if f(x) > 0 and y > 0 and y <= f(x):
                ctr += 1 # area over x-axis is positive
            if f(x) < 0 and y < 0 and y >= f(x):
                ctr -= 1 # area under x-axis is negative

    fnArea = rectArea * float(ctr) / numPoints
    return fnArea
