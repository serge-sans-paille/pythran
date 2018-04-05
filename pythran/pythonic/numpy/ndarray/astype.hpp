#ifndef PYTHONIC_NUMPY_NDARRAY_ASTYPE_HPP
#define PYTHONIC_NUMPY_NDARRAY_ASTYPE_HPP

#include "pythonic/include/numpy/ndarray/astype.hpp"
#include "pythonic/numpy/asarray.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace ndarray
  {

    template <class E, class dtype>
    auto astype(E &&e, dtype d) -> typename std::enable_if<
        types::is_array<typename std::decay<E>::type>::value,
        decltype(asarray(std::forward<E>(e), d))>::type
    {
      return asarray(std::forward<E>(e), d);
    }
    template <class E, class dtype>
    auto astype(E &&e, dtype d) -> typename std::enable_if<
        !types::is_array<typename std::decay<E>::type>::value,
        typename dtype::type>::type
    {
      return std::forward<E>(e);
    }

    DEFINE_FUNCTOR(pythonic::numpy::ndarray, astype);
  }
}
PYTHONIC_NS_END

#endif
