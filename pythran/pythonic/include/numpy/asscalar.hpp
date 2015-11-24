#ifndef PYTHONIC_INCLUDE_NUMPY_ASSCALAR_HPP
#define PYTHONIC_INCLUDE_NUMPY_ASSCALAR_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/numpy/asarray.hpp"
#include "pythonic/include/__builtin__/ValueError.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class E>
    typename E::dtype asscalar(E const &expr);

    DECLARE_FUNCTOR(pythonic::numpy, asscalar);
  }
}

#endif
