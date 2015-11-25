#ifndef PYTHONIC_INCLUDE_NUMPY_LDEXP_HPP
#define PYTHONIC_INCLUDE_NUMPY_LDEXP_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/types/numpy_broadcast.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"
#include <nt2/include/functions/ldexp.hpp>

namespace pythonic
{

  namespace numpy
  {
    namespace wrapper
    {
      template <class T, class U>
      double ldexp(T const &v, U const &u);
    }

#define NUMPY_NARY_FUNC_NAME ldexp
#define NUMPY_NARY_FUNC_SYM wrapper::ldexp
#include "pythonic/include/types/numpy_nary_expr.hpp"
  }
}

#endif
