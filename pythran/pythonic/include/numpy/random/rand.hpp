#ifndef PYTHONIC_INCLUDE_NUMPY_RANDOM_RAND_HPP
#define PYTHONIC_INCLUDE_NUMPY_RANDOM_RAND_HPP

#include "pythonic/include/utils/proxy.hpp"
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

      PROXY_DECL(pythonic::numpy::random, rand);
    }
  }
}

#endif
