#ifndef PYTHONIC_INCLUDE_NUMPY_DIGITIZE_HPP
#define PYTHONIC_INCLUDE_NUMPY_DIGITIZE_HPP

#include "pythonic/include/numpy/asarray.hpp"
#include "pythonic/include/__builtin__/None.hpp"
#include "pythonic/include/operator_/gt.hpp"
#include "pythonic/include/operator_/lt.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class I, class O, class B, class Op>
    void _digitize(I begin, I end, O &out, B &bins, Op const &op,
                   utils::int_<1>);

    template <class I, class O, class B, class Op, size_t N>
    void _digitize(I begin, I end, O &out, B &bins, Op const &op,
                   utils::int_<N>);

    template <class E, class F>
    types::ndarray<long, 1> digitize(E const &expr, F const &b);

    DECLARE_FUNCTOR(pythonic::numpy, digitize);
  }
}

#endif
