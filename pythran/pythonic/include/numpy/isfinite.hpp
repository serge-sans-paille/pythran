#ifndef PYTHONIC_INCLUDE_NUMPY_ISFINITE_HPP
#define PYTHONIC_INCLUDE_NUMPY_ISFINITE_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"

#include <nt2/include/functions/is_finite.hpp>

// nt2 does not handle bool specialization, which is indeed a corner case...
namespace nt2
{
  constexpr bool is_finite(bool);
}

namespace pythonic
{

  namespace numpy
  {
    namespace wrapper
    {
      template <class T>
      bool isfinite(T const &v);
    }

#define NUMPY_NARY_FUNC_NAME isfinite
#define NUMPY_NARY_FUNC_SYM wrapper::isfinite
#include "pythonic/include/types/numpy_nary_expr.hpp"
  }
}

#endif
