#ifndef PYTHONIC_INCLUDE_NUMPY_RANDOM_RAND_HPP
#define PYTHONIC_INCLUDE_NUMPY_RANDOM_RAND_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"

namespace pythonic
{
  namespace numpy
  {
    namespace random
    {
      template <class... T>
      types::ndarray<double, sizeof...(T)> rand(T... shape);

      double rand();

      DECLARE_FUNCTOR(pythonic::numpy::random, rand);
    }
  }
}

#endif
