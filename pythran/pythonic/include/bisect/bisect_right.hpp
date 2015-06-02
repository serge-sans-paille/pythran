#ifndef PYTHONIC_INCLUDE_BISECT_BISECTRIGHT_HPP
#define PYTHONIC_INCLUDE_BISECT_BISECTRIGHT_HPP

#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace bisect
  {
    template <class X, class A>
    long bisect_right(X const &x, A const &a, long lo = 0);

    template <class X, class A>
    long bisect_right(X const &x, A const &a, long lo, long hi);

    PROXY_DECL(pythonic::bisect, bisect_right);
  }
}

#endif
