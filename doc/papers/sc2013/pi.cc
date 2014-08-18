#include <stddef.h>
#include <stdlib.h>
static
double pi(size_t nsteps) {
  double sum = 0., step = 1. / nsteps;
  #pragma omp parallel for reduction(+:sum)
  for(size_t i = 0; i < nsteps ; ++i)
  {
      double x = (i - 0.5) * step;
      sum += 4. / (1. + x * x);
  }
  return step * sum;
}

#include <stdio.h>
#include <omp.h>
int main(int argc, char * argv[]) {
    int n = atoi(argv[1]);
    double start = omp_get_wtime();
    double p = pi(n);
    double stop = omp_get_wtime();
    printf("%lf\n", stop - start);
    return p;
}
