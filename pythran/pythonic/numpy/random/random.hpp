#ifndef PYTHONIC_NUMPY_RANDOM_RANDOM_HPP
#define PYTHONIC_NUMPY_RANDOM_RANDOM_HPP

#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/numpy_expr.hpp"

#include <random>

namespace pythonic {
namespace numpy {
namespace random {

  namespace details {
      std::default_random_engine generator;
  }

  template<size_t N>
  types::ndarray<double, N> random(types::array<long, N> const& shape)
  {
    types::ndarray<double, N> result{shape, types::none_type()};
    std::uniform_real_distribution<double> distribution{0., 1.};
    std::generate(result.fbegin(), result.fend(), [&]() { return distribution(details::generator); });
    return result;
  }

  auto random(long size) -> decltype(random(types::array<long, 1>{{size}}))
  {
    return random(types::array<long, 1>{{size}});
  }

  double random(types::none_type d = types::none_type())
  {
    return std::uniform_real_distribution<double>{0., 1.}(details::generator);
  }

  PROXY(pythonic::numpy::random, random);

}
}
}

#endif
