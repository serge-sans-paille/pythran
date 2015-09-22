#ifndef PYTHONIC_INCLUDE_OPERATOR_INVERT_HPP
#define PYTHONIC_INCLUDE_OPERATOR_INVERT_HPP

#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace operator_
  {

    template <class A>
    decltype(~std::declval<A const &>()) invert(A const &a);

    PROXY_DECL(pythonic::operator_, invert);
  }
}

#endif
