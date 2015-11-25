#ifndef PYTHONIC_INCLUDE_NUMPY_RANK_HPP
#define PYTHONIC_INCLUDE_NUMPY_RANK_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class E>
    size_t rank(E const &expr);

    DECLARE_FUNCTOR(pythonic::numpy, rank);
  }
}

#endif
