#ifndef PYTHONIC_INCLUDE_OPERATOR_NOT_HPP
#define PYTHONIC_INCLUDE_OPERATOR_NOT_HPP

#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace operator_
  {
    template <class T>
    decltype(!std::declval<T const &>()) not_(T const &a);

    PROXY_DECL(pythonic::operator_, not_);
  }
}

#endif
