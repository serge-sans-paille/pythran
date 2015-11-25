#ifndef PYTHONIC_INCLUDE_NUMPY_SQUARE_HPP
#define PYTHONIC_INCLUDE_NUMPY_SQUARE_HPP

#include "pythonic/include/types/numpy_op_helper.hpp"
#include "pythonic/include/utils/meta.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"
#include "pythonic/include/utils/functor.hpp"

#include <nt2/include/functions/sqr.hpp>

#ifdef USE_GMP
#include "pythonic/include/types/long.hpp"

namespace nt2
{
  template <class T, class U>
  auto sqr(__gmp_expr<T, U> const &a) -> decltype(a *a);
}

#endif

namespace pythonic
{

  namespace numpy
  {

#define NUMPY_NARY_FUNC_NAME square
#define NUMPY_NARY_FUNC_SYM nt2::sqr
#include "pythonic/include/types/numpy_nary_expr.hpp"
  }
}

#endif
