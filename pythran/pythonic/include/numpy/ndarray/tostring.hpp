#ifndef PYTHONIC_INCLUDE_NUMPY_NDARRAY_TOSTRING_HPP
#define PYTHONIC_INCLUDE_NUMPY_NDARRAY_TOSTRING_HPP

#include "pythonic/utils/functor.hpp"
#include "pythonic/utils/numpy_conversion.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/str.hpp"

namespace pythonic
{

  namespace numpy
  {

    namespace ndarray
    {
      template <class T, size_t N>
      types::str tostring(types::ndarray<T, N> const &expr);

      NUMPY_EXPR_TO_NDARRAY0_DECL(tostring);
      DECLARE_FUNCTOR(pythonic::numpy::ndarray, tostring);
    }
  }
}
#endif
