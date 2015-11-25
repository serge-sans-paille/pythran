#ifndef PYTHONIC_INCLUDE_NUMPY_NANMAX_HPP
#define PYTHONIC_INCLUDE_NUMPY_NANMAX_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/__builtin__/ValueError.hpp"
#include "pythonic/include/numpy/isnan.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class E, class F>
    void _nanmax(E begin, E end, F &max, utils::int_<1>);

    template <class E, class F, size_t N>
    void _nanmax(E begin, E end, F &max, utils::int_<N>);

    template <class E>
    typename E::dtype nanmax(E const &expr);

    DECLARE_FUNCTOR(pythonic::numpy, nanmax);
  }
}

#endif
