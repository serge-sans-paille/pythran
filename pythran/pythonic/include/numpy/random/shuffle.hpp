#ifndef PYTHONIC_INCLUDE_NUMPY_RANDOM_SHUFFLE_HPP
#define PYTHONIC_INCLUDE_NUMPY_RANDOM_SHUFFLE_HPP

#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/types/NoneType.hpp"
#include "pythonic/include/numpy/random/generator.hpp"

namespace pythonic
{
  namespace numpy
  {
    namespace random
    {
      template <class T>
      types::none_type shuffle(T &seq);

      DECLARE_FUNCTOR(pythonic::numpy::random, shuffle);
    }
  }
}

#endif
