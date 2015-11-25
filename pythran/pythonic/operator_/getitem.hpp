#ifndef PYTHONIC_OPERATOR_GETITEM_HPP
#define PYTHONIC_OPERATOR_GETITEM_HPP

#include "pythonic/include/operator_/getitem.hpp"

#include "pythonic/utils/functor.hpp"

namespace pythonic
{

  namespace operator_
  {
    template <class A, class B>
    auto getitem(A const &a, B const &b) -> decltype(a[b])
    {
      return a[b];
    }

    DEFINE_FUNCTOR(pythonic::operator_, getitem);
  }
}

#endif
