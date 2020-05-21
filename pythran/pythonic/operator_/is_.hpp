#ifndef PYTHONIC_OPERATOR_IS_HPP
#define PYTHONIC_OPERATOR_IS_HPP

#include "pythonic/include/operator_/is_.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/builtins/id.hpp"

PYTHONIC_NS_BEGIN

namespace operator_
{

  template <class A, class B>
  auto is_(A const &a, B const &b)
      -> decltype(builtins::id(a) == builtins::id(b))
  {
    return builtins::id(a) == builtins::id(b);
  }
}
PYTHONIC_NS_END

#endif
