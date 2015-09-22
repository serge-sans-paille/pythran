#ifndef PYTHONIC_INCLUDE_OPERATOR_ISNOT_HPP
#define PYTHONIC_INCLUDE_OPERATOR_ISNOT_HPP

#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace operator_
  {

    template <class A, class B>
    auto is_not(A const &a, B const &b) -> decltype(a != b);

    PROXY_DECL(pythonic::operator_, is_not);
  }
}

#endif
