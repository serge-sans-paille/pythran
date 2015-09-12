#ifndef PYTHONIC_INCLUDE_OPERATOR_OR_HPP
#define PYTHONIC_INCLUDE_OPERATOR_OR_HPP

#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace operator_
  {

    template <class A, class B>
    auto or_(A const &a, B const &b) -> decltype(a | b);

    PROXY_DECL(pythonic::operator_, or_);
  }
}

#endif
