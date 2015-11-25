#ifndef PYTHONIC_INCLUDE_OPERATOR_FLOORDIV_HPP
#define PYTHONIC_INCLUDE_OPERATOR_FLOORDIV_HPP

#include "pythonic/include/utils/functor.hpp"
#include <nt2/include/functions/divfloor.hpp>

namespace pythonic
{

  namespace operator_
  {
    long floordiv(long a, long b);
    long floordiv(long long a, long b);
    long floordiv(long long a, long long b);
    long floordiv(long a, long long b);
    template <class T, class U>
    double floordiv(T a, U b);

    DECLARE_FUNCTOR(pythonic::operator_, floordiv);
  }
}

#endif
