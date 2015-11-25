#ifndef PYTHONIC_INCLUDE_OPERATOR_TRUEDIV_HPP
#define PYTHONIC_INCLUDE_OPERATOR_TRUEDIV_HPP

#include "pythonic/include/utils/functor.hpp"

namespace pythonic
{

  namespace operator_
  {
    template <class A, class B>
    auto truediv(A const &a, B const &b) -> decltype(a / (double)b);

    DECLARE_FUNCTOR(pythonic::operator_, truediv);
  }
}

#endif
