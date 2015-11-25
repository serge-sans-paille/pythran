#ifndef PYTHONIC_NUMPY_NDARRAY_TOSTRING_HPP
#define PYTHONIC_NUMPY_NDARRAY_TOSTRING_HPP

#include "pythonic/include/numpy/ndarray/tostring.hpp"

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
      types::str tostring(types::ndarray<T, N> const &expr)
      {
        return types::str(reinterpret_cast<const char *>(expr.buffer),
                          expr.flat_size() * sizeof(T));
      }
      NUMPY_EXPR_TO_NDARRAY0_IMPL(tostring);
      DEFINE_FUNCTOR(pythonic::numpy::ndarray, tostring);
    }
  }
}
#endif
