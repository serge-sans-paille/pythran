#ifndef PYTHONIC_INCLUDE_NUMPY_PUTMASK_HPP
#define PYTHONIC_INCLUDE_NUMPY_PUTMASK_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/numpy/asarray.hpp"
#include "pythonic/include/__builtin__/None.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class T, size_t N, class E, class F>
    types::none_type putmask(types::ndarray<T, N> &expr, E const &mask,
                             F const &values);

    template <class E, class M, class F>
    types::none_type putmask(E &, M const &, F const &);

    DECLARE_FUNCTOR(pythonic::numpy, putmask);
  }
}

#endif
