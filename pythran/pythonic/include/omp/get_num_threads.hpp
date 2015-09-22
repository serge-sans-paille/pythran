#ifndef PYTHONIC_INCLUDE_OMP_GET_NUM_THREADS_HPP
#define PYTHONIC_INCLUDE_OMP_GET_NUM_THREADS_HPP

#include <omp.h>

#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace omp
  {

    long get_num_threads();

    PROXY_DECL(pythonic::omp, get_num_threads);
  }
}

#endif
