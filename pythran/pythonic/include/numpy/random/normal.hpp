#ifndef PYTHONIC_INCLUDE_NUMPY_RANDOM_NORMAL_HPP
#define PYTHONIC_INCLUDE_NUMPY_RANDOM_NORMAL_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/types/NoneType.hpp"
#include "pythonic/include/types/tuple.hpp"

namespace pythonic
{
  namespace numpy
  {
    namespace random
    {
      template <size_t N>
      types::ndarray<double, N> normal(double loc, double scale,
                                       types::array<long, N> const &shape);

      auto normal(double loc, double scale, long size)
          -> decltype(normal(loc, scale, types::array<long, 1>{{size}}));

      double normal(double loc = 0.0, double scale = 1.0,
                    types::none_type size = {});

      DECLARE_FUNCTOR(pythonic::numpy::random, normal);
    }
  }
}

#endif
