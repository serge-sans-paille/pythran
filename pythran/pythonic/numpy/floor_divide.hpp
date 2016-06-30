#ifndef PYTHONIC_NUMPY_FLOORDIVIDE_HPP
#define PYTHONIC_NUMPY_FLOORDIVIDE_HPP

#include "pythonic/include/numpy/floor_divide.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/numpy_broadcast.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include <nt2/include/functions/divfloor.hpp>

namespace nt2
{

  template <class F, class I>
  typename std::enable_if<
      std::is_floating_point<F>::value && std::is_integral<I>::value, F>::type
  divfloor(F x, I y)
  {
    return divfloor(x, (F)y);
  }

  template <class F, class I>
  typename std::enable_if<
      std::is_floating_point<F>::value && std::is_integral<I>::value, F>::type
  divfloor(I x, F y)
  {
    return divfloor((F)x, y);
  }
}

namespace pythonic
{

  namespace numpy
  {
#define NUMPY_NARY_FUNC_NAME floor_divide
#define NUMPY_NARY_FUNC_SYM nt2::divfloor
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif
