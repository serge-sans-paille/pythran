#ifndef PYTHONIC_INCLUDE_NUMPY_RANDOM_BINOMIAL_HPP
#define PYTHONIC_INCLUDE_NUMPY_RANDOM_BINOMIAL_HPP

#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/types/numpy_expr.hpp"

#include "pythonic/include/numpy/random/generator.hpp"

namespace pythonic
{
  namespace numpy
  {
    namespace random
    {
      template <size_t N>
      types::ndarray<long, N> binomial(double n, double p,
                                       types::array<long, N> const &shape);

      auto binomial(double n, double p, long size)
          -> decltype(binomial(n, p, types::array<long, 1>{{size}}));

      long binomial(double n, double p,
                    types::none_type d = types::none_type());

      DECLARE_FUNCTOR(pythonic::numpy::random, binomial);
    }
  }
}

#endif
