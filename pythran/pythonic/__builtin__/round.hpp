#ifndef PYTHONIC_BUILTIN_ROUND_HPP
#define PYTHONIC_BUILTIN_ROUND_HPP

#include "pythonic/include/__builtin__/round.hpp"

#include "pythonic/__builtin__/pow.hpp"
#include "pythonic/utils/functor.hpp"

#include <cmath>

namespace pythonic
{

  namespace __builtin__
  {

    template <class T>
    double round(T const &v, size_t n)
    {
      T p = functor::pow()(10, n);
      return std::lround(v * p) / p;
    }

    template <class T>
    double round(T const &v)
    {
      return std::lround(v);
    }

    DEFINE_FUNCTOR(pythonic::__builtin__, round);
  }
}

#endif
