#ifndef PYTHONIC_NUMPY_RANDOM_RAND_HPP
#define PYTHONIC_NUMPY_RANDOM_RAND_HPP

#include "pythonic/include/numpy/random/rand.hpp"

#include "pythonic/numpy/random/random.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/tuple.hpp"
#include "pythonic/utils/functor.hpp"

namespace pythonic
{
  namespace numpy
  {
    namespace random
    {

      template <class... T>
      types::ndarray<double, sizeof...(T)> rand(T... shape)
      {
        return random(types::array<long, sizeof...(T)>{{shape...}});
      }

      double rand()
      {
        return random();
      }

      DEFINE_FUNCTOR(pythonic::numpy::random, rand);
    }
  }
}

#endif
