#ifndef PYTHONIC_OPERATOR_FLOORDIV_HPP
#define PYTHONIC_OPERATOR_FLOORDIV_HPP

#include "pythonic/include/operator_/floordiv.hpp"

#include "pythonic/utils/functor.hpp"
#include <nt2/include/functions/divfloor.hpp>

namespace pythonic
{

  namespace operator_
  {

    long floordiv(long a, long b)
    {
      return std::floor(static_cast<double>(a) / b);
    }

    long floordiv(long long a, long b)
    {
      return std::floor(static_cast<double>(a) / b);
    }

    long floordiv(long long a, long long b)
    {
      return std::floor(static_cast<double>(a) / b);
    }

    long floordiv(long a, long long b)
    {
      return std::floor(static_cast<double>(a) / b);
    }

    template <class T, class U>
    double floordiv(T a, U b)
    {
      return std::floor(a / b);
    }

    DEFINE_FUNCTOR(pythonic::operator_, floordiv);
  }
}

#endif
