#ifndef PYTHONIC_INCLUDE_BISECT_BISECTLEFT_HPP
#define PYTHONIC_INCLUDE_BISECT_BISECTLEFT_HPP

#include "pythonic/include/utils/functor.hpp"

namespace pythonic
{

  namespace bisect
  {
    template <class X, class A>
    long bisect_left(X const &x, A const &a, long lo = 0);

    template <class X, class A>
    long bisect_left(X const &x, A const &a, long lo, long hi);

    DECLARE_FUNCTOR(pythonic::bisect, bisect_left);
  }
}

#endif
