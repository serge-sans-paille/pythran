#ifndef PYTHONIC_NUMPY_ISNAN_HPP
#define PYTHONIC_NUMPY_ISNAN_HPP

#include "pythonic/include/numpy/isnan.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/utils/numpy_traits.hpp"

#include <nt2/include/functions/is_nan.hpp>

// nt2 does not handle bool specialization, which is indeed a corner case...
namespace nt2
{
  constexpr bool is_nan(bool)
  {
    return false;
  }
}

namespace pythonic
{

  namespace numpy
  {
    namespace wrapper
    {
      template <class T>
      bool isnan(T const &v)
      {
        return nt2::is_nan(v);
      }
    }

#define NUMPY_NARY_FUNC_NAME isnan
#define NUMPY_NARY_FUNC_SYM wrapper::isnan
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif
