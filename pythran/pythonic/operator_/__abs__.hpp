#ifndef PYTHONIC_OPERATOR_ABS_HPP
#define PYTHONIC_OPERATOR_ABS_HPP

#include "pythonic/include/operator_/__abs__.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/builtins/abs.hpp"

namespace pythonic
{

  namespace operator_
  {

    template <class A>
    auto __abs__(A const &a) -> decltype(builtins::abs(a))
    {
      return builtins::abs(a);
    }

    PROXY_IMPL(pythonic::operator_, __abs__);
  }
}

#endif
