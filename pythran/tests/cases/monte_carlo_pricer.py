#unittest.skip np.random not supported yet
import numpy as np
def step(dt, prices, c0, c1, noises):
    return prices * np.exp(c0 * dt + c1 * noises)

def monte_carlo_pricer(paths, dt, interest, volatility):
    c0 = interest - 0.5 * volatility ** 2
    c1 = volatility * np.sqrt(dt)

    for j in xrange(1, paths.shape[1]): # for all trials
        prices = paths[:, j - 1]
        # generate normally distributed random number
        noises = np.random.normal(0., 1., prices.size)
        # calculate the next batch of prices for all trials
        paths[:, j] = step(dt, prices, c0, c1, noises)
