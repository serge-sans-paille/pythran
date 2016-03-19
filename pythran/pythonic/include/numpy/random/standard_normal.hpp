#ifndef PYTHONIC_INCLUDE_NUMPY_RANDOM_STANDARD_NORMAL_HPP
#define PYTHONIC_INCLUDE_NUMPY_RANDOM_STANDARD_NORMAL_HPP

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
      types::ndarray<double, N>
      standard_normal(types::array<long, N> const &shape);

      auto standard_normal(long size)
          -> decltype(standard_normal(types::array<long, 1>{{size}}));

      double standard_normal(types::none_type d = {});

      DECLARE_FUNCTOR(pythonic::numpy::random, standard_normal);
    }
  }
}

#endif
