#ifndef PYTHONIC_NUMPY_ISFINITE_HPP
#define PYTHONIC_NUMPY_ISFINITE_HPP

#include "pythonic/include/numpy/isfinite.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/utils/numpy_traits.hpp"

#include <nt2/include/functions/is_finite.hpp>

// nt2 does not handle bool specialization, which is indeed a corner case...
namespace nt2
{
  constexpr bool is_finite(bool)
  {
    return true;
  }
}

namespace pythonic
{

  namespace numpy
  {
    namespace wrapper
    {
      template <class T>
      bool isfinite(T const &v)
      {
        return nt2::is_finite(v);
      }
    }

#define NUMPY_NARY_FUNC_NAME isfinite
#define NUMPY_NARY_FUNC_SYM wrapper::isfinite
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif
