#ifndef PYTHONIC_NUMPY_ISNEGINF_HPP
#define PYTHONIC_NUMPY_ISNEGINF_HPP

#include "pythonic/include/numpy/isneginf.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include <nt2/include/functions/is_inf.hpp>
#include <nt2/include/functions/is_negative.hpp>

namespace pythonic
{

  namespace numpy
  {
    namespace wrapper
    {
      template <class T>
      auto isneginf(T const &t)
          -> decltype(nt2::is_inf(t) and nt2::is_negative(t))
      {
        return nt2::is_inf(t) and nt2::is_negative(t);
      }
    }

#define NUMPY_NARY_FUNC_NAME isneginf
#define NUMPY_NARY_FUNC_SYM wrapper::isneginf
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif
