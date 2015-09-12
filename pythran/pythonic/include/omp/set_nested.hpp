#ifndef PYTHONIC_INCLUDE_OMP_SET_NESTED_HPP
#define PYTHONIC_INCLUDE_OMP_SET_NESTED_HPP

#include <omp.h>
#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace omp
  {

    void set_nested(long val);

    PROXY_DECL(pythonic::omp, set_nested);
  }
}

#endif
