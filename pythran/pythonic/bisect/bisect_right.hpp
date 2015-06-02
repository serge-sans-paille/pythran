#ifndef PYTHONIC_BISECT_BISECTRIGHT_HPP
#define PYTHONIC_BISECT_BISECTRIGHT_HPP

#include "pythonic/include/bisect/bisect_right.hpp"

#include "pythonic/bisect/bisect.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace bisect
  {

    template <class X, class A>
    long bisect_right(X const &x, A const &a, long lo)
    {
      return bisect(x, a, lo);
    }

    template <class X, class A>
    long bisect_right(X const &x, A const &a, long lo, long hi)
    {
      return bisect(x, a, lo, hi);
    }

    PROXY_IMPL(pythonic::bisect, bisect_right);
  }
}

#endif
