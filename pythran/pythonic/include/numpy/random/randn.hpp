#ifndef PYTHONIC_INCLUDE_NUMPY_RANDOM_RANDN_HPP
#define PYTHONIC_INCLUDE_NUMPY_RANDOM_RANDN_HPP

#include "pythonic/include/numpy/random/generator.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/utils/functor.hpp"

namespace pythonic
{
  namespace numpy
  {
    namespace random
    {
      template <class... T>
      types::ndarray<double, sizeof...(T)> randn(T... shape);

      double randn();

      DECLARE_FUNCTOR(pythonic::numpy::random, randn);
    }
  }
}

#endif
