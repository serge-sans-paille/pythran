import numpy as np
#pythran export collatz(int)
#runas collatz(10)

def collatz(n_max):
  n = np.arange(3, n_max+1)
  count = np.ones_like(n)
  indices = n != 1
  while np.any(indices):
    count[indices] += 1
    x = n[indices]
    n[indices] = np.where(x & 1, 3 * x + 1, x // 2)
    indices = n != 1
  max_i = np.argmax(count)
  return max_i + 3, count[max_i]
