#ifndef PYTHONIC_OPERATOR_OR_HPP
#define PYTHONIC_OPERATOR_OR_HPP

#include "pythonic/include/operator_/or_.hpp"

#include "pythonic/utils/functor.hpp"

namespace pythonic
{

  namespace operator_
  {

    template <class A, class B>
    auto or_(A const &a, B const &b) -> decltype(a | b)
    {
      return a | b;
    }

    DEFINE_FUNCTOR(pythonic::operator_, or_);
  }
}

#endif
