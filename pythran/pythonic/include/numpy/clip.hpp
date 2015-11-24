#ifndef PYTHONIC_INCLUDE_NUMPY_CLIP_HPP
#define PYTHONIC_INCLUDE_NUMPY_CLIP_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {
    namespace wrapper
    {
      template <class T, class Mi, class Ma>
      typename __combined<T, Mi, Ma>::type clip(T const &v, Mi a_min, Ma a_max);

      template <class T, class Mi>
      typename __combined<T, Mi>::type clip(T const &v, Mi a_min);
    }

#define NUMPY_NARY_FUNC_NAME clip
#define NUMPY_NARY_FUNC_SYM wrapper::clip
#include "pythonic/include/types/numpy_nary_expr.hpp"
  }
}

#endif
