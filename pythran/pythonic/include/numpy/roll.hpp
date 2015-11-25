#ifndef PYTHONIC_INCLUDE_NUMPY_ROLL_HPP
#define PYTHONIC_INCLUDE_NUMPY_ROLL_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/utils/numpy_conversion.hpp"
#include "pythonic/include/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class T, size_t N>
    types::ndarray<T, N> roll(types::ndarray<T, N> const &expr, long shift);

    template <class To, class From, size_t N>
    To _roll(To to, From from, long, long, types::array<long, N> const &,
             utils::int_<0>);

    template <class To, class From, size_t N, size_t M>
    To _roll(To to, From from, long shift, long axis,
             types::array<long, N> const &shape, utils::int_<M>);

    template <class T, size_t N>
    types::ndarray<T, N> roll(types::ndarray<T, N> const &expr, long shift,
                              long axis);

    NUMPY_EXPR_TO_NDARRAY0_DECL(roll);
    DECLARE_FUNCTOR(pythonic::numpy, roll);
  }
}

#endif
