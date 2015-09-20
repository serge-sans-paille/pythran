#ifndef PYTHONIC_INCLUDE_NUMPY_RANDOM_RANDOM_HPP
#define PYTHONIC_INCLUDE_NUMPY_RANDOM_RANDOM_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/types/none.hpp"
#include "pythonic/include/types/tuple.hpp"

namespace pythonic
{
  namespace numpy
  {
    namespace random
    {
      template <size_t N>
      types::ndarray<double, N> random(types::array<long, N> const &shape);

      auto random(long size) -> decltype(random(types::array<long, 1>{{size}}));

      double random(types::none_type d = types::none_type());

      PROXY_DECL(pythonic::numpy::random, random);
    }
  }
}

#endif
