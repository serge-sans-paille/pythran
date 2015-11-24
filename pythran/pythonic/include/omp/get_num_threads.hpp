#ifndef PYTHONIC_INCLUDE_OMP_GET_NUM_THREADS_HPP
#define PYTHONIC_INCLUDE_OMP_GET_NUM_THREADS_HPP

#include <omp.h>

#include "pythonic/include/utils/functor.hpp"

namespace pythonic
{

  namespace omp
  {

    long get_num_threads();

    DECLARE_FUNCTOR(pythonic::omp, get_num_threads);
  }
}

#endif
