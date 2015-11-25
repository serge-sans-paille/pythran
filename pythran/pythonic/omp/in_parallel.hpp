#ifndef PYTHONIC_OMP_IN_PARALLEL_HPP
#define PYTHONIC_OMP_IN_PARALLEL_HPP

#include "pythonic/include/omp/in_parallel.hpp"

#include <omp.h>
#include "pythonic/utils/functor.hpp"

namespace pythonic
{

  namespace omp
  {

    bool in_parallel()
    {
      return omp_in_parallel();
    }

    DEFINE_FUNCTOR(pythonic::omp, in_parallel);
  }
}

#endif
