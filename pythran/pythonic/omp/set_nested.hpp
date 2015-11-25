#ifndef PYTHONIC_OMP_SET_NESTED_HPP
#define PYTHONIC_OMP_SET_NESTED_HPP

#include "pythonic/include/omp/set_nested.hpp"

#include <omp.h>
#include "pythonic/utils/functor.hpp"

namespace pythonic
{

  namespace omp
  {

    void set_nested(long val)
    {
      return omp_set_nested(val);
    }

    DEFINE_FUNCTOR(pythonic::omp, set_nested);
  }
}

#endif
