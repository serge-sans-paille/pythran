#ifndef PYTHONIC_INCLUDE_OPERATOR_XOR__HPP
#define PYTHONIC_INCLUDE_OPERATOR_XOR__HPP

#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace operator_
  {
    template <class A, class B>
    auto __xor__(A const &a, B const &b) -> decltype(a ^ b);

    PROXY_DECL(pythonic::operator_, __xor__);
  }
}

#endif
