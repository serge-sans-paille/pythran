#ifndef PYTHONIC_INCLUDE_NUMPY_MOD_HPP
#define PYTHONIC_INCLUDE_NUMPY_MOD_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/types/assignable.hpp"
#include "pythonic/include/operator_/mod.hpp"

namespace pythonic
{

  namespace numpy
  {

    /* this is still a numpy_expr, because operator::mod_ forwards to
     * operator% which is correctly overloaded
     */

    using operator_::mod;
    PROXY_DECL(pythonic::numpy, mod);
  }
}

#endif
