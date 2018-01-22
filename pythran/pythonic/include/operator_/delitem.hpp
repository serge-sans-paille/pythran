#ifndef PYTHONIC_INCLUDE_OPERATOR_DELITEM_HPP
#define PYTHONIC_INCLUDE_OPERATOR_DELITEM_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/__builtin__/None.hpp"

PYTHONIC_NS_BEGIN

namespace operator_
{
  template <class A, class B>
  types::none_type delitem(A &&a, B const &b);

  DECLARE_FUNCTOR(pythonic::operator_, delitem);
}
PYTHONIC_NS_END

#endif
