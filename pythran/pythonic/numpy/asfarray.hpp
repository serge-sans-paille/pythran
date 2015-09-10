#ifndef PYTHONIC_NUMPY_ASFARRAY_HPP
#define PYTHONIC_NUMPY_ASFARRAY_HPP

#include "pythonic/include/numpy/asfarray.hpp"
#include "pythonic/numpy/asarray.hpp"
#include "pythonic/types/numpy_type.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class E, class dtype>
    auto asfarray(E &&e, dtype d) -> decltype(asarray(std::forward<E>(e), d))
    {
      static_assert(std::is_floating_point<
                        typename types::numpy_type<dtype>::type>::value,
                    "expected a floating point type");
      return asarray(std::forward<E>(e), d);
    }
    PROXY_IMPL(pythonic::numpy, asfarray);
  }
}

#endif
