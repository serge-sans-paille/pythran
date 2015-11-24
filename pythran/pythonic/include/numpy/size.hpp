#ifndef PYTHONIC_INCLUDE_NUMPY_SIZE_HPP
#define PYTHONIC_INCLUDE_NUMPY_SIZE_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {

    template <class E>
    auto size(E const &e) -> decltype(e.flat_size());

    DECLARE_FUNCTOR(pythonic::numpy, size)
  }
}

#endif
