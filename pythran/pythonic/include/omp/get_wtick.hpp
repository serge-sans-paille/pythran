#ifndef PYTHONIC_INCLUDE_OMP_GET_WTICK_HPP
#define PYTHONIC_INCLUDE_OMP_GET_WTICK_HPP

#include <omp.h>
#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace omp
  {
    long get_wtick();

    PROXY_DECL(pythonic::omp, get_wtick);
  }
}

#endif
