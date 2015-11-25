#ifndef PYTHONIC_OPERATOR_INDEXOF_HPP
#define PYTHONIC_OPERATOR_INDEXOF_HPP

#include "pythonic/include/operator_/indexOf.hpp"

#include "pythonic/utils/functor.hpp"

namespace pythonic
{

  namespace operator_
  {

    template <class A, class B>
    long indexOf(A const &a, B const &b)
    {
      return a.index(b);
    }

    DEFINE_FUNCTOR(pythonic::operator_, indexOf);
  }
}

#endif
