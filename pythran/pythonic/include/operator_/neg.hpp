#ifndef PYTHONIC_INCLUDE_OPERATOR_NEG_HPP
#define PYTHONIC_INCLUDE_OPERATOR_NEG_HPP

#include "pythonic/include/utils/functor.hpp"

namespace pythonic
{

  namespace operator_
  {

    template <class A>
    auto neg(A const &a) -> decltype(-a);

    DECLARE_FUNCTOR(pythonic::operator_, neg);
  }
}

#endif
