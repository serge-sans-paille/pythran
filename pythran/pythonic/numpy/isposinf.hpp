#ifndef PYTHONIC_NUMPY_ISPOSINF_HPP
#define PYTHONIC_NUMPY_ISPOSINF_HPP

#include "pythonic/include/numpy/isposinf.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/utils/numpy_traits.hpp"

#include <nt2/include/functions/is_inf.hpp>
#include <nt2/include/functions/is_positive.hpp>

namespace pythonic
{

  namespace numpy
  {
    namespace wrapper
    {
      template <class T>
      bool isposinf(T const &t)
      {
        return nt2::is_inf(t) and nt2::is_positive(t);
      }
    }
#define NUMPY_NARY_FUNC_NAME isposinf
#define NUMPY_NARY_FUNC_SYM wrapper::isposinf
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif
