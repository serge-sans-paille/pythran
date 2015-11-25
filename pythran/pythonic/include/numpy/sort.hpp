#ifndef PYTHONIC_INCLUDE_NUMPY_SORT_HPP
#define PYTHONIC_INCLUDE_NUMPY_SORT_HPP

#include <algorithm>

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"

namespace pythonic
{
  namespace numpy
  {

    template <class T>
    bool _comp(T const &i, T const &j);

    template <class T>
    bool _comp(std::complex<T> const &i, std::complex<T> const &j);

    template <class T, size_t N>
    void _sort(types::ndarray<T, N> &out, long axis);

    template <class T, size_t N>
    types::ndarray<T, N> sort(types::ndarray<T, N> const &expr, long axis = -1);

    NUMPY_EXPR_TO_NDARRAY0_DECL(sort);
    DECLARE_FUNCTOR(pythonic::numpy, sort);
  }
}

#endif
