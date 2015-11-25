#ifndef PYTHONIC_INCLUDE_NUMPY_ARGMAX_HPP
#define PYTHONIC_INCLUDE_NUMPY_ARGMAX_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/numpy/asarray.hpp"
#include "pythonic/include/__builtin__/ValueError.hpp"

namespace pythonic
{

  namespace numpy
  {

    template <class I0, class T>
    long _argmax(I0 begin, I0 end, T &max_elts, utils::int_<1>);

    template <class I0, size_t N, class T>
    long _argmax(I0 begin, I0 end, T &max_elts, utils::int_<N>);

    template <class E>
    long argmax(E const &expr);

    DECLARE_FUNCTOR(pythonic::numpy, argmax);
  }
}

#endif
