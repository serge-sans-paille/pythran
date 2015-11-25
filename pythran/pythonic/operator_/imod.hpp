#ifndef PYTHONIC_OPERATOR_IMOD_HPP
#define PYTHONIC_OPERATOR_IMOD_HPP

#include "pythonic/include/operator_/imod.hpp"

#include "pythonic/utils/functor.hpp"

namespace pythonic
{

  namespace operator_
  {

    template <class A, class B>
    A imod(A a, B const &b)
    {
      return a %= b;
    }

    DEFINE_FUNCTOR(pythonic::operator_, imod);
  }
}

#endif
