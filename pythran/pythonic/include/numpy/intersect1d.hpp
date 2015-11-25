#ifndef PYTHONIC_INCLUDE_NUMPY_INTERSECT1D_HPP
#define PYTHONIC_INCLUDE_NUMPY_INTERSECT1D_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/types/combined.hpp"
#include "pythonic/include/numpy/asarray.hpp"

#include <algorithm>

namespace pythonic
{

  namespace numpy
  {
    template <class E, class F>
    types::ndarray<
        typename __combined<typename E::dtype, typename F::dtype>::type, 1>
    intersect1d(E const &e, F const &f);

    DECLARE_FUNCTOR(pythonic::numpy, intersect1d);
  }
}

#endif
