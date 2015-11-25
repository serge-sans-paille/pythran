#ifndef PYTHONIC_NUMPY_ASSCALAR_HPP
#define PYTHONIC_NUMPY_ASSCALAR_HPP

#include "pythonic/include/numpy/asscalar.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/numpy/asarray.hpp"
#include "pythonic/__builtin__/ValueError.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class E>
    typename E::dtype asscalar(E const &expr)
    {
      if (expr.flat_size() != 1)
        throw types::ValueError(
            "can only convert an array  of size 1 to a Python scalar");
      return *asarray(expr).fbegin();
    }

    DEFINE_FUNCTOR(pythonic::numpy, asscalar);
  }
}

#endif
