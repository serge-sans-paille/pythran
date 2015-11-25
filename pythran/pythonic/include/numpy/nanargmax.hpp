#ifndef PYTHONIC_INCLUDE_NUMPY_NANARGMAX_HPP
#define PYTHONIC_INCLUDE_NUMPY_NANARGMAX_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/__builtin__/ValueError.hpp"
#include "pythonic/include/numpy/isnan.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class E, class F>
    void _nanargmax(E begin, E end, F &max, long &index, long &where,
                    utils::int_<1>);

    template <class E, class F, size_t N>
    void _nanargmax(E begin, E end, F &max, long &index, long &where,
                    utils::int_<N>);

    template <class E>
    typename E::dtype nanargmax(E const &expr);

    DECLARE_FUNCTOR(pythonic::numpy, nanargmax);
  }
}

#endif
