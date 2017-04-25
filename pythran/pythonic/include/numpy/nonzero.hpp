#ifndef PYTHONIC_INCLUDE_NUMPY_NONZERO_HPP
#define PYTHONIC_INCLUDE_NUMPY_NONZERO_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {

    template <class E>
    auto nonzero(E const &expr)
        -> types::array<types::ndarray<long, 1>, E::value>;

    DECLARE_FUNCTOR(pythonic::numpy, nonzero)
  }
}

#endif
