#ifndef PYTHONIC_INCLUDE_SCIPY_SPECIAL_EVAL_LEGENDRE_HPP
#define PYTHONIC_INCLUDE_SCIPY_SPECIAL_EVAL_LEGENDRE_HPP

#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"

PYTHONIC_NS_BEGIN

namespace scipy
{
  namespace special
  {

    namespace details
    {
      template <class T>
      double eval_legendre(int n, T x);
    }

#define NUMPY_NARY_FUNC_NAME eval_legendre
#define NUMPY_NARY_FUNC_SYM details::eval_legendre
#include "pythonic/include/types/numpy_nary_expr.hpp"
  }
}
PYTHONIC_NS_END

#endif
