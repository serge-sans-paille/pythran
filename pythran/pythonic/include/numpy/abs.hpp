#ifndef PYTHONIC_INCLUDE_NUMPY_ABS_HPP
#define PYTHONIC_INCLUDE_NUMPY_ABS_HPP

#include "pythonic/include/types/numpy_op_helper.hpp"
#include "pythonic/include/utils/meta.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"
#include "pythonic/include/utils/functor.hpp"

#include <nt2/sdk/complex/complex.hpp>
#include <nt2/include/functions/abs.hpp>

// nt2 does not handle bool specialization, which is indeed a corner case...
namespace nt2
{
  constexpr bool abs(bool v);
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
#include "pythonic/include/types/numpy_nary_expr.hpp"
  }
}

#endif
