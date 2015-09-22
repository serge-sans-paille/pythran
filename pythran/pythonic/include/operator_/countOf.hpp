#ifndef PYTHONIC_INCLUDE_OPERATOR_COUNTOF_HPP
#define PYTHONIC_INCLUDE_OPERATOR_COUNTOF_HPP

#include "pythonic/include/utils/proxy.hpp"
#include <algorithm>

namespace pythonic
{

  namespace operator_
  {
    template <class A, class B>
    long countOf(A const &a, B const &b);

    PROXY_DECL(pythonic::operator_, countOf);
  }
}

#endif
