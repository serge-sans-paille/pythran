#ifndef PYTHONIC_INCLUDE_NUMPY_SQUARE_HPP
#define PYTHONIC_INCLUDE_NUMPY_SQUARE_HPP

#include "pythonic/include/types/numpy_op_helper.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"
#include "pythonic/include/utils/functor.hpp"

#include <complex>

namespace wrapper
{
}

PYTHONIC_NS_BEGIN

namespace numpy
{

  namespace wrapper
  {
    template <class T>
    auto square(T const &arg) -> decltype(arg *arg)
    {
      return arg * arg;
    }
  }

#define NUMPY_NARY_FUNC_NAME square
#define NUMPY_NARY_FUNC_SYM wrapper::square
#include "pythonic/include/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
