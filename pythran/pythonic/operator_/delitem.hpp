#ifndef PYTHONIC_OPERATOR_DELITEM_HPP
#define PYTHONIC_OPERATOR_DELITEM_HPP

#include "pythonic/include/operator_/delitem.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/builtins/None.hpp"

namespace pythonic
{

  namespace operator_
  {

    template <class A, class B>
    types::none_type delitem(A &&a, B const &b)
    {
      a.remove(b);
      return builtins::None;
    }

    PROXY_IMPL(pythonic::operator_, delitem);
  }
}

#endif
