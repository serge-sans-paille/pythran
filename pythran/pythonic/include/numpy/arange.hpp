#ifndef PYTHONIC_INCLUDE_NUMPY_ARANGE_HPP
#define PYTHONIC_INCLUDE_NUMPY_ARANGE_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/types/numpy_type.hpp"
#include "pythonic/include/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class T, class U, class S = long,
              class dtype = decltype(std::declval<T>() + std::declval<U>() +
                                     std::declval<S>())>
    types::ndarray<typename types::numpy_type<dtype>::type, 1>
    arange(T begin, U end, S step = S(1), dtype d = dtype());

    template <class T>
    types::ndarray<T, 1> arange(T end);

    PROXY_DECL(pythonic::numpy, arange);
  }
}

#endif
