#ifndef PYTHONIC_INCLUDE_OPERATOR_AND_HPP
#define PYTHONIC_INCLUDE_OPERATOR_AND_HPP

#include "pythonic/include/utils/functor.hpp"

namespace pythonic
{

  namespace operator_
  {
    template <class A, class B>
    auto and_(A const &a, B const &b) -> decltype(a &b);

    DECLARE_FUNCTOR(pythonic::operator_, and_);
  }
}

#endif
