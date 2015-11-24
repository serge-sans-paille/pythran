#ifndef PYTHONIC_INCLUDE_OMP_GET_WTICK_HPP
#define PYTHONIC_INCLUDE_OMP_GET_WTICK_HPP

#include <omp.h>
#include "pythonic/include/utils/functor.hpp"

namespace pythonic
{

  namespace omp
  {
    long get_wtick();

    DECLARE_FUNCTOR(pythonic::omp, get_wtick);
  }
}

#endif
