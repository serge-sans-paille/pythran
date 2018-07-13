#ifndef PYTHONIC_INCLUDE_BUILTIN_PYTHRAN_STATIC_IF_HPP
#define PYTHONIC_INCLUDE_BUILTIN_PYTHRAN_STATIC_IF_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/__builtin__/pythran/is_none.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  namespace pythran
  {
    template <class T, class F0, class F1>
    typename std::conditional<std::is_same<T, types::true_type>::value, F0,
                              F1>::type
    static_if_(T const &cond, F0 f0, F1 f1);

    DEFINE_FUNCTOR(pythonic::__builtin__::pythran, static_if_);
  }
}
PYTHONIC_NS_END

#endif
