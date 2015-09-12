#ifndef PYTHONIC_INCLUDE_OPERATOR_ABS_HPP
#define PYTHONIC_INCLUDE_OPERATOR_ABS_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/__builtin__/abs.hpp"

namespace pythonic
{

  namespace operator_
  {

    template <class A>
    auto __abs__(A const &a) -> decltype(__builtin__::abs(a));

    PROXY_DECL(pythonic::operator_, __abs__);
  }
}

#endif
