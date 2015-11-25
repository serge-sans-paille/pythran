#ifndef PYTHONIC_INCLUDE_OMP_SET_NESTED_HPP
#define PYTHONIC_INCLUDE_OMP_SET_NESTED_HPP

#include <omp.h>
#include "pythonic/include/utils/functor.hpp"

namespace pythonic
{

  namespace omp
  {

    void set_nested(long val);

    DECLARE_FUNCTOR(pythonic::omp, set_nested);
  }
}

#endif
