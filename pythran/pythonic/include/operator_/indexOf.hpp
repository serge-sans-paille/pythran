#ifndef PYTHONIC_INCLUDE_OPERATOR_INDEXOF_HPP
#define PYTHONIC_INCLUDE_OPERATOR_INDEXOF_HPP

#include "pythonic/include/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace operator_
{

  template <class C, class V, class... Args>
  long indexOf(C const &c, V &&v, Args &&...args);

  DEFINE_FUNCTOR(pythonic::operator_, indexOf);
} // namespace operator_
PYTHONIC_NS_END

#endif
