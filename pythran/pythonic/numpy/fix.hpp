#ifndef PYTHONIC_NUMPY_FIX_HPP
#define PYTHONIC_NUMPY_FIX_HPP

#include "pythonic/include/numpy/fix.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include <nt2/include/functions/trunc.hpp>

namespace pythonic
{

  namespace numpy
  {
    namespace wrapper
    {
      template <class T>
      double fix(T const &v)
      {
        return nt2::trunc(v);
      }
    }

#define NUMPY_NARY_FUNC_NAME fix
#define NUMPY_NARY_FUNC_SYM wrapper::fix
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif
