#ifndef PYTHONIC_INCLUDE_NUMPY_ISNAN_HPP
#define PYTHONIC_INCLUDE_NUMPY_ISNAN_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"

#include <nt2/include/functions/is_nan.hpp>

// nt2 does not handle bool specialization, which is indeed a corner case...
namespace nt2
{
  constexpr bool is_nan(bool);
}

namespace pythonic
{

  namespace numpy
  {
    namespace wrapper
    {
      template <class T>
      bool isnan(T const &v);
    }

#define NUMPY_NARY_FUNC_NAME isnan
#define NUMPY_NARY_FUNC_SYM wrapper::isnan
#include "pythonic/include/types/numpy_nary_expr.hpp"
  }
}

#endif
