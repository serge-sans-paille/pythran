#ifndef PYTHONIC_INCLUDE_OMP_GET_WTIME_HPP
#define PYTHONIC_INCLUDE_OMP_GET_WTIME_HPP

#include <omp.h>
#include "pythonic/include/utils/functor.hpp"

namespace pythonic
{

  namespace omp
  {

    long get_wtime();

    DECLARE_FUNCTOR(pythonic::omp, get_wtime);
  }
}

#endif
