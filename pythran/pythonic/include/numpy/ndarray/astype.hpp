#ifndef PYTHONIC_INCLUDE_NUMPY_NDARRAY_ASTYPE_HPP
#define PYTHONIC_INCLUDE_NUMPY_NDARRAY_ASTYPE_HPP

#include "pythonic/include/numpy/asarray.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace ndarray
  {

    template <class E, class dtype>
    auto astype(E &&e, dtype d) -> typename std::enable_if<
        types::is_array<typename std::decay<E>::type>::value,
        decltype(asarray(std::forward<E>(e), d))>::type;

    template <class E, class dtype> // extension selected by pythran for
                                    // numpy.float64.astype and cie
                                    auto astype(E &&e, dtype d) ->
        typename std::enable_if<
            !types::is_array<typename std::decay<E>::type>::value,
            typename dtype::type>::type;

    DECLARE_FUNCTOR(pythonic::numpy::ndarray, astype);
  }
}
PYTHONIC_NS_END

#endif
