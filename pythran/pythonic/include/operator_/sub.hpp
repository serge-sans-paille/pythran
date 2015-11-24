#ifndef PYTHONIC_INCLUDE_OPERATOR_SUB_HPP
#define PYTHONIC_INCLUDE_OPERATOR_SUB_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/operator_/overloads.hpp"

namespace pythonic
{

  namespace operator_
  {

    template <class A, class B>
    auto sub(A const &a, B const &b) -> decltype(a - b);

    DEFINE_ALL_OPERATOR_OVERLOADS_DECL(sub, -)

    DECLARE_FUNCTOR(pythonic::operator_, sub);
  }
}

#endif
