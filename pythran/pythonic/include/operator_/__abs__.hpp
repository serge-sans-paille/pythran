#ifndef PYTHONIC_INCLUDE_OPERATOR_ABS_HPP
#define PYTHONIC_INCLUDE_OPERATOR_ABS_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/builtins/abs.hpp"

namespace pythonic
{

  namespace operator_
  {

    template <class A>
    auto __abs__(A const &a) -> decltype(builtins::abs(a));

    PROXY_DECL(pythonic::operator_, __abs__);
  }
}

#endif
