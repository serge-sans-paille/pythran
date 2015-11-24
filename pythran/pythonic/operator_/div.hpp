#ifndef PYTHONIC_OPERATOR_DIV_HPP
#define PYTHONIC_OPERATOR_DIV_HPP

#include "pythonic/include/operator_/div.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/operator_/overloads.hpp"
#ifdef USE_BOOST_SIMD
#include <nt2/include/functions/divides.hpp>
#endif

namespace pythonic
{

  namespace operator_
  {
    template <class A, class B>
    auto div(A const &a, B const &b) -> decltype(a / b)
    {
      return a / b;
    }

    DEFINE_ALL_OPERATOR_OVERLOADS_IMPL(div, / )

    DEFINE_FUNCTOR(pythonic::operator_, div);
  }
}

#endif
