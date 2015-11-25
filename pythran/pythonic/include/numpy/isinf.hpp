#ifndef PYTHONIC_INCLUDE_NUMPY_ISINF_HPP
#define PYTHONIC_INCLUDE_NUMPY_ISINF_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"
#include <nt2/include/functions/is_inf.hpp>

namespace pythonic
{

  namespace numpy
  {
    namespace wrapper
    {
      template <class T>
      bool isinf(T const &v);
    }
#define NUMPY_NARY_FUNC_NAME isinf
#define NUMPY_NARY_FUNC_SYM wrapper::isinf
#include "pythonic/include/types/numpy_nary_expr.hpp"
  }
}

#endif
