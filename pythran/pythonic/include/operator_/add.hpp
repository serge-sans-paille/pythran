#ifndef PYTHONIC_INCLUDE_OPERATOR_ADD_HPP
#define PYTHONIC_INCLUDE_OPERATOR_ADD_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/operator_/overloads.hpp"

namespace pythonic
{

  namespace operator_
  {
    template <class A, class B>
    auto add(A const &a, B const &b) -> decltype(a + b);

    DEFINE_ALL_OPERATOR_OVERLOADS_DECL(add, +)

    PROXY_DECL(pythonic::operator_, add);
  }
}

#endif
