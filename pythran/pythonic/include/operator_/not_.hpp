#ifndef PYTHONIC_INCLUDE_OPERATOR_NOT_HPP
#define PYTHONIC_INCLUDE_OPERATOR_NOT_HPP

#include "pythonic/include/utils/functor.hpp"

namespace pythonic
{

  namespace operator_
  {
    template <class T>
    decltype(!std::declval<T const &>()) not_(T const &a);

    DECLARE_FUNCTOR(pythonic::operator_, not_);
  }
}

#endif
