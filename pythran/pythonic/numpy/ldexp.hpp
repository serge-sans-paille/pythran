#ifndef PYTHONIC_NUMPY_LDEXP_HPP
#define PYTHONIC_NUMPY_LDEXP_HPP

#include "pythonic/include/numpy/ldexp.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/numpy_broadcast.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include <nt2/include/functions/ldexp.hpp>

namespace pythonic
{

  namespace numpy
  {
    namespace wrapper
    {
      template <class T, class U>
      double ldexp(T const &v, U const &u)
      {
        return nt2::ldexp(v, u);
      }
    }

#define NUMPY_NARY_FUNC_NAME ldexp
#define NUMPY_NARY_FUNC_SYM wrapper::ldexp
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif
