#ifndef PYTHONIC_INCLUDE_OPERATOR_TRUEDIV_HPP
#define PYTHONIC_INCLUDE_OPERATOR_TRUEDIV_HPP

#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace operator_
  {
    template <class A, class B>
    auto truediv(A const &a, B const &b) -> decltype(a / (double)b);

    PROXY_DECL(pythonic::operator_, truediv);
  }
}

#endif
