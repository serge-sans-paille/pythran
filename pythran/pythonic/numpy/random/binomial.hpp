#ifndef PYTHONIC_NUMPY_RANDOM_BINOMIAL_HPP
#define PYTHONIC_NUMPY_RANDOM_BINOMIAL_HPP

#include "pythonic/include/numpy/random/binomial.hpp"

#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/numpy_expr.hpp"

#include "pythonic/types/exceptions.hpp"

namespace pythonic
{
  namespace numpy
  {
    namespace random
    {
      namespace details
      {
        inline void parameters_check(double n, double p)
        {
          if (n < 0)
            throw pythonic::types::ValueError("n < 0");
          if (p < 0)
            throw pythonic::types::ValueError("p < 0");
          else if (p > 1)
            throw pythonic::types::ValueError("p > 1");
        }
      }

      template <size_t N>
      types::ndarray<long, N> binomial(double n, double p,
                                       types::array<long, N> const &shape)
      {
        details::parameters_check(n, p);
        types::ndarray<long, N> result{shape, types::none_type()};
        std::binomial_distribution<long> distribution{(long)n, p};
        std::generate(result.fbegin(), result.fend(),
                      [&]() { return distribution(details::generator); });
        return result;
      }

      auto binomial(double n, double p, long size)
          -> decltype(binomial(n, p, types::array<long, 1>{{size}}))
      {
        return binomial(n, p, types::array<long, 1>{{size}});
      }

      long binomial(double n, double p, types::none_type d)
      {
        details::parameters_check(n, p);
        return std::binomial_distribution<long>{(long)n, p}(details::generator);
      }

      DEFINE_FUNCTOR(pythonic::numpy::random, binomial);
    }
  }
}

#endif
