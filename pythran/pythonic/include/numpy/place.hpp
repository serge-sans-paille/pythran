#ifndef PYTHONIC_INCLUDE_NUMPY_PLACE_HPP
#define PYTHONIC_INCLUDE_NUMPY_PLACE_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/__builtin__/None.hpp"
#include "pythonic/include/numpy/asarray.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class T, size_t N, class Tp, size_t Np, class F>
    types::none_type place(types::ndarray<T, N> &expr,
                           types::ndarray<Tp, Np> const &mask, F const &values);

    template <class T, size_t N, class M, class F>
    types::none_type place(types::ndarray<T, N> &expr, M const &mask,
                           F const &values);

    template <class E, class M, class F>
    types::none_type place(E &, M const &, F const &);

    DECLARE_FUNCTOR(pythonic::numpy, place);
  }
}

#endif
