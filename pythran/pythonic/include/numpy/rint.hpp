#ifndef PYTHONIC_INCLUDE_NUMPY_RINT_HPP
#define PYTHONIC_INCLUDE_NUMPY_RINT_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"
#include <nt2/include/functions/iround2even.hpp>

namespace pythonic
{

  namespace numpy
  {
    namespace wrapper
    {
      template <class T>
      T rint(T const &v);
    }
#define NUMPY_NARY_FUNC_NAME rint
#define NUMPY_NARY_FUNC_SYM wrapper::rint
#include "pythonic/include/types/numpy_nary_expr.hpp"
  }
}

#endif
