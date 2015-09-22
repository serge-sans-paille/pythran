#ifndef PYTHONIC_INCLUDE_OPERATOR_IMOD_HPP
#define PYTHONIC_INCLUDE_OPERATOR_IMOD_HPP

#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace operator_
  {

    template <class A, class B>
    A imod(A a, B const &b);

    PROXY_DECL(pythonic::operator_, imod);
  }
}

#endif
