#ifndef PYTHONIC_OPERATOR_LT_HPP
#define PYTHONIC_OPERATOR_LT_HPP

#include "pythonic/include/operator_/lt.hpp"

#include "pythonic/utils/functor.hpp"

namespace pythonic
{

  namespace operator_
  {

    template <class A, class B>
    auto lt(A const &a, B const &b) -> decltype(a < b)
    {
      return a < b;
    }

    DEFINE_FUNCTOR(pythonic::operator_, lt);
  }
}

#endif
