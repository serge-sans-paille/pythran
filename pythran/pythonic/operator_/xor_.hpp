#ifndef PYTHONIC_OPERATOR_XOR_HPP
#define PYTHONIC_OPERATOR_XOR_HPP

#include "pythonic/include/operator_/xor_.hpp"

#include "pythonic/utils/functor.hpp"

namespace pythonic
{

  namespace operator_
  {
    template <class A, class B>
    auto xor_(A const &a, B const &b) -> decltype(a ^ b)
    {
      return a ^ b;
    }

    DEFINE_FUNCTOR(pythonic::operator_, xor_);
  }
}

#endif
