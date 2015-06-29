#ifndef PYTHONIC_BUILTIN_ROUND_HPP
#define PYTHONIC_BUILTIN_ROUND_HPP

#include "pythonic/include/builtins/round.hpp"

#include "pythonic/builtins/pow.hpp"
#include "pythonic/utils/proxy.hpp"

#include <cmath>

namespace pythonic
{

  namespace builtins
  {

    template <class T>
    double round(T const &v, size_t n)
    {
      T p = proxy::pow()(10, n);
      return std::lround(v * p) / p;
    }

    template <class T>
    double round(T const &v)
    {
      return std::lround(v);
    }

    PROXY_IMPL(pythonic::builtins, round);
  }
}

#endif
