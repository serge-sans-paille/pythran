#pythran export pi(int)
def pi(nsteps):
  sum, step = 0., 1. / nsteps
  "omp parallel for reduction(+:sum) private(x)"
  for i in range(nsteps):
      x = (i - 0.5) * step
      sum += 4. / (1. + x**2)
  return step * sum
