#ifndef PYTHONIC_NUMPY_RANDOM_STANDARD_NORMAL_HPP
#define PYTHONIC_NUMPY_RANDOM_STANDARD_NORMAL_HPP

#include "pythonic/include/numpy/random/standard_normal.hpp"
#include "pythonic/include/numpy/random/generator.hpp"

#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/none.hpp"
#include "pythonic/types/tuple.hpp"
#include "pythonic/utils/proxy.hpp"

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
        types::ndarray<double, N> result{shape, types::none_type()};
        std::normal_distribution<double> distribution{0., 1.};
        std::generate(result.fbegin(), result.fend(),
                      [&]() { return distribution(details::generator); });
        return result;
      }

      auto standard_normal(long size)
          -> decltype(standard_normal(types::array<long, 1>{{size}}))
      {
        return standard_normal(types::array<long, 1>{{size}});
      }

      double standard_normal(types::none_type d)
      {
        return std::normal_distribution<double>{0., 1.}(details::generator);
      }

      PROXY_IMPL(pythonic::numpy::random, standard_normal);
    }
  }
}

#endif
