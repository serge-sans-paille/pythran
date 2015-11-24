#ifndef PYTHONIC_INCLUDE_NUMPY_BINCOUNT_HPP
#define PYTHONIC_INCLUDE_NUMPY_BINCOUNT_HPP

#include "pythonic/include/numpy/max.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class T, size_t N>
    types::ndarray<long, 1>
    bincount(types::ndarray<T, N> const &expr,
             types::none_type weights = __builtin__::None,
             types::none<long> minlength = __builtin__::None);

    template <class T, size_t N, class E>
    types::ndarray<
        decltype(std::declval<long>() * std::declval<typename E::dtype>()), 1>
    bincount(types::ndarray<T, N> const &expr, E const &weights,
             types::none<long> minlength = __builtin__::None);

    DECLARE_FUNCTOR(pythonic::numpy, bincount);
  }
}

#endif
