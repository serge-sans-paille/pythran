#ifndef PYTHONIC_NUMPY_SQUARE_HPP
#define PYTHONIC_NUMPY_SQUARE_HPP

#include "pythonic/include/numpy/square.hpp"

#include "pythonic/utils/numpy_traits.hpp"
#include "pythonic/utils/functor.hpp"

#include <nt2/include/functions/sqr.hpp>

#ifdef USE_GMP
#include "pythonic/types/long.hpp"

namespace nt2
{
  template <class T, class U>
  auto sqr(__gmp_expr<T, U> const &a) -> decltype(a *a)
  {
    return a * a;
  }
}

#endif

namespace pythonic
{

  namespace numpy
  {

#define NUMPY_NARY_FUNC_NAME square
#define NUMPY_NARY_FUNC_SYM nt2::sqr
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif
