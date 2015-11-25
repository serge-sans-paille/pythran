#ifndef PYTHONIC_NUMPY_MOD_HPP
#define PYTHONIC_NUMPY_MOD_HPP

#include "pythonic/include/numpy/mod.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/assignable.hpp"
#include "pythonic/operator_/mod.hpp"

namespace pythonic
{

  namespace numpy
  {

    /* this is still a numpy_expr, because operator::mod_ forwards to
     * operator% which is correctly overloaded
     */

    using operator_::mod;
    DEFINE_FUNCTOR(pythonic::numpy, mod);
  }
}

#endif
