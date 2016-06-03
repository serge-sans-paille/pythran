#ifndef PYTHONIC_NUMPY_ABS_HPP
#define PYTHONIC_NUMPY_ABS_HPP

#include "pythonic/include/numpy/abs.hpp"

#include "pythonic/utils/functor.hpp"

// nt2 does not handle bool specialization, which is indeed a corner case...
namespace nt2
{
  constexpr bool abs(bool v)
  {
    return v;
  }
}

namespace pythonic
{

  namespace numpy
  {

#define NUMPY_NARY_FUNC_NAME abs
#ifdef USE_BOOST_SIMD
#define NUMPY_NARY_FUNC_SYM nt2::abs
#else
#define NUMPY_NARY_FUNC_SYM std::abs
#endif
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif
