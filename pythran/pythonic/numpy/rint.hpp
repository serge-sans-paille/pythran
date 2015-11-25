#ifndef PYTHONIC_NUMPY_RINT_HPP
#define PYTHONIC_NUMPY_RINT_HPP

#include "pythonic/include/numpy/rint.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include <nt2/include/functions/iround2even.hpp>

namespace pythonic
{

  namespace numpy
  {
    namespace wrapper
    {

      template <class T>
      T rint(T const &v)
      {
        return nt2::iround2even(v);
      }
    }
#define NUMPY_NARY_FUNC_NAME rint
#define NUMPY_NARY_FUNC_SYM wrapper::rint
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif
