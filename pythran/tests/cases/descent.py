#pythran export np_descent(float64[], float64[], float, int)
#from https://realpython.com/numpy-tensorflow-performance/#using-tensorflow
#runas import numpy as np; np.random.seed(444); N = 10000; sigma = 0.1; noise = sigma * np.random.randn(N); x = np.linspace(0, 2, N); d = 3 + 2 * x + noise; mu = 0.001; N_epochs = 10000; np_descent(x, d, mu, N_epochs)

import itertools as it
import numpy as np

def np_descent(x, d, mu, N_epochs):
    N = len(x)
    f = 2 / N

    y = np.zeros(N)
    err = np.zeros(N)
    w = np.zeros(2)
    grad = np.empty(2)

    for _ in it.repeat(None, N_epochs):
        #np.subtract(d, y, out=err)
        err[:] = d - y
        grad[:] = f * np.sum(err), f * (np.dot(err, x))
        w += mu * grad
        y = w[0] + w[1] * x
    return w
