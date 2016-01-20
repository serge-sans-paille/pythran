#ifndef PYTHONIC_INCLUDE_NUMPY_NDARRAY_ASTYPE_HPP
#define PYTHONIC_INCLUDE_NUMPY_NDARRAY_ASTYPE_HPP

#include "pythonic/include/numpy/asarray.hpp"

namespace pythonic
{

  namespace numpy
  {
    namespace ndarray
    {

      template <class E, class dtype>
      auto astype(E &&e, dtype d) -> decltype(asarray(std::forward<E>(e), d));

      DECLARE_FUNCTOR(pythonic::numpy::ndarray, astype);
    }
  }
}

#endif
