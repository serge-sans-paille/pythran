#ifndef PYTHONIC_NUMPY_ISNEGINF_HPP
#define PYTHONIC_NUMPY_ISNEGINF_HPP

#include "pythonic/include/numpy/isneginf.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/utils/numpy_traits.hpp"

namespace pythonic
{

  namespace numpy
  {
    namespace wrapper
    {
      template <class T>
      auto isneginf(T const &t)
          -> decltype(boost::simd::is_inf(t) and boost::simd::is_negative(t))
      {
        return boost::simd::is_inf(t) and boost::simd::is_negative(t);
      }
    }

#define NUMPY_NARY_FUNC_NAME isneginf
#define NUMPY_NARY_FUNC_SYM wrapper::isneginf
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif
