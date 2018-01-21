#ifndef PYTHONIC_BUILTIN_PYTHRAN_IFEXP_HPP
#define PYTHONIC_BUILTIN_PYTHRAN_IFEXP_HPP

#include "pythonic/include/__builtin__/pythran/ifexp.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/combined.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  namespace pythran
  {

    template <class T0, class T1>
    types::lazy_combined_t<T0, T1> ifexp(bool cond, T0 &&v0, T1 &&v1)
    {
      if (cond)
        return std::forward<T0>(v0)();
      else
        return std::forward<T1>(v1)();
    }

    DEFINE_FUNCTOR(pythonic::__builtin__::pythran, ifexp);
  }
}
PYTHONIC_NS_END

#endif
