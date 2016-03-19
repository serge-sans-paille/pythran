#ifndef PYTHONIC_NUMPY_RANDOM_STANDARD_NORMAL_HPP
#define PYTHONIC_NUMPY_RANDOM_STANDARD_NORMAL_HPP

#include "pythonic/include/numpy/random/standard_normal.hpp"
#include "pythonic/include/numpy/random/generator.hpp"

#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/NoneType.hpp"
#include "pythonic/types/tuple.hpp"
#include "pythonic/utils/functor.hpp"
#include "pythonic/numpy/random/normal.hpp"

#include <random>
#include <algorithm>

namespace pythonic
{
  namespace numpy
  {
    namespace random
    {

      template <size_t N>
      types::ndarray<double, N>
      standard_normal(types::array<long, N> const &shape)
      {
        return normal(0., 1., shape);
      }

      auto standard_normal(long size)
          -> decltype(standard_normal(types::array<long, 1>{{size}}))
      {
        return standard_normal(types::array<long, 1>{{size}});
      }

      double standard_normal(types::none_type d)
      {
        return normal(0., 1., d);
      }

      DEFINE_FUNCTOR(pythonic::numpy::random, standard_normal);
    }
  }
}

#endif
