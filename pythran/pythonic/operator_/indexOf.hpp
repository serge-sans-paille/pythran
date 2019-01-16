#ifndef PYTHONIC_OPERATOR_INDEXOF_HPP
#define PYTHONIC_OPERATOR_INDEXOF_HPP

#include "pythonic/include/operator_/indexOf.hpp"

#include "pythonic/__builtin__/str.hpp"
#include "pythonic/types/exceptions.hpp"
#include "pythonic/utils/functor.hpp"

#include <algorithm>

PYTHONIC_NS_BEGIN

namespace operator_
{

  template <class A, class B>
  long indexOf(A const &a, B const &b)
  {
    auto where = std::find(a.begin(), a.end(), b);
    if (where == a.end())
      throw types::ValueError(__builtin__::anonymous::str(b) +
                              " is not in this sequence");
    return where - a.begin();
  }
}
PYTHONIC_NS_END

#endif
