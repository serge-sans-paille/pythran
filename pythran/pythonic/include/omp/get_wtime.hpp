#ifndef PYTHONIC_INCLUDE_OMP_GET_WTIME_HPP
#define PYTHONIC_INCLUDE_OMP_GET_WTIME_HPP

#include <omp.h>
#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace omp
  {

    long get_wtime();

    PROXY_DECL(pythonic::omp, get_wtime);
  }
}

#endif
