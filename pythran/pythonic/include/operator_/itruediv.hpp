#ifndef PYTHONIC_INCLUDE_OPERATOR_ITRUEDIV_HPP
#define PYTHONIC_INCLUDE_OPERATOR_ITRUEDIV_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/operator_/truediv.hpp"

namespace pythonic
{

  namespace operator_
  {
    template <class A, class B>
    auto itruediv(A a, B const &b) -> decltype(truediv(a, b));

    PROXY_DECL(pythonic::operator_, itruediv);
  }
}

#endif
