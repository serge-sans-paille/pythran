#ifndef PYTHONIC_OPERATOR_NE_HPP
#define PYTHONIC_OPERATOR_NE_HPP

#include "pythonic/include/operator_/ne.hpp"

#include "pythonic/utils/functor.hpp"

namespace pythonic
{

  namespace operator_
  {

    template <class A, class B>
    auto ne(A const &a, B const &b) -> decltype(a != b)
    {
      return a != b;
    }

    DEFINE_FUNCTOR(pythonic::operator_, ne);
  }
}

#endif
