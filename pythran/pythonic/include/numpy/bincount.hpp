#ifndef PYTHONIC_INCLUDE_NUMPY_BINCOUNT_HPP
#define PYTHONIC_INCLUDE_NUMPY_BINCOUNT_HPP

#include "pythonic/numpy/max.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class T, size_t N>
    types::ndarray<long, 1>
    bincount(types::ndarray<T, N> const &expr,
             types::none_type weights = builtins::None,
             types::none<long> minlength = builtins::None);

    template <class T, size_t N, class E>
    types::ndarray<
        decltype(std::declval<long>() * std::declval<typename E::dtype>()), 1>
    bincount(types::ndarray<T, N> const &expr, E const &weights,
             types::none<long> minlength = builtins::None);

    PROXY_DECL(pythonic::numpy, bincount);
  }
}

#endif
