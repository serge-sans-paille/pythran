#ifndef PYTHONIC_NUMPY_ISINF_HPP
#define PYTHONIC_NUMPY_ISINF_HPP

#include "pythonic/include/numpy/isinf.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include <nt2/include/functions/is_inf.hpp>

namespace pythonic
{

  namespace numpy
  {
    namespace wrapper
    {
      template <class T>
      bool isinf(T const &v)
      {
        return nt2::is_inf(v);
      }
    }
#define NUMPY_NARY_FUNC_NAME isinf
#define NUMPY_NARY_FUNC_SYM wrapper::isinf
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif
