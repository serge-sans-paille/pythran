#ifndef PYTHONIC_INCLUDE_NUMPY_FLATNONZERO_HPP
#define PYTHONIC_INCLUDE_NUMPY_FLATNONZERO_HPP

#include "pythonic/include/numpy/asarray.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class I, class O>
    void _flatnonzero(I begin, I end, O &out, long &i, utils::int_<1>);

    template <class I, class O, size_t N>
    void _flatnonzero(I begin, I end, O &out, long &i, utils::int_<N>);

    template <class E>
    types::ndarray<long, 1> flatnonzero(E const &expr);

    DECLARE_FUNCTOR(pythonic::numpy, flatnonzero);
  }
}

#endif
