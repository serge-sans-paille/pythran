#ifndef PYTHONIC_INCLUDE_OPERATOR_IS_HPP
#define PYTHONIC_INCLUDE_OPERATOR_IS_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/builtins/id.hpp"

PYTHONIC_NS_BEGIN

namespace operator_
{

  template <class A, class B>
  auto is_(A const &a, B const &b)
      -> decltype(builtins::id(a) == builtins::id(b));

  DEFINE_FUNCTOR(pythonic::operator_, is_);
}
PYTHONIC_NS_END

#endif
