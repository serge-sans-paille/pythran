#ifndef PYTHONIC_INCLUDE_OMP_GET_THREAD_NUM_HPP
#define PYTHONIC_INCLUDE_OMP_GET_THREAD_NUM_HPP

#include <omp.h>
#include "pythonic/include/utils/functor.hpp"

namespace pythonic
{

  namespace omp
  {

    long get_thread_num();

    DECLARE_FUNCTOR(pythonic::omp, get_thread_num);
  }
}

#endif
