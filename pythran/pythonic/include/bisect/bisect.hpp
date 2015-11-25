#ifndef PYTHONIC_INCLUDE_BISECT_BISECT_HPP
#define PYTHONIC_INCLUDE_BISECT_BISECT_HPP

#include "pythonic/include/utils/functor.hpp"

#include <algorithm>

namespace pythonic
{

  namespace bisect
  {
    namespace details
    {
      template <class X, class A>
      using bisect_fun =
          decltype(std::upper_bound<typename X::const_iterator, A>);
    }

    template <class X, class A>
    long bisect(X const &x, A const &a, long lo = 0,
                details::bisect_fun<X, A> const &fun =
                    std::upper_bound<typename X::const_iterator, A>);

    template <class X, class A>
    long bisect(X const &x, A const &a, long lo, long hi,
                details::bisect_fun<X, A> const &fun =
                    std::upper_bound<typename X::const_iterator, A>);

    DECLARE_FUNCTOR(pythonic::bisect, bisect);
  }
}

#endif
