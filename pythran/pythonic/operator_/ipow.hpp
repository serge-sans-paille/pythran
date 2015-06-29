#ifndef PYTHONIC_OPERATOR_IPOW_HPP
#define PYTHONIC_OPERATOR_IPOW_HPP

#include "pythonic/include/operator_/ipow.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/builtins/pow.hpp"

namespace pythonic
{

  namespace operator_
  {

    template <class A, class B>
    A ipow(A a, B const &b)
    {
      return a = builtins::pow(a, b);
    }

    PROXY_IMPL(pythonic::operator_, ipow);
  }
}

#endif
