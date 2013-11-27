#pythran export np1(float [])
import numpy as np
def np1(x):
  return np.sum(100.*(x[1:] - x[:-1] ** 2) ** 2
                + (1. - x[:-1]) ** 2)
