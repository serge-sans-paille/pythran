#ifndef PYTHONIC_BUILTIN_PYTHRAN_OR_HPP
#define PYTHONIC_BUILTIN_PYTHRAN_OR_HPP

#include "pythonic/include/__builtin__/pythran/or_.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/combined.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  namespace pythran
  {

    template <class T0, class T1>
    types::lazy_combined_t<T0, T1> or_(T0 &&v0, T1 &&v1)
    {
      auto &&val0 = std::forward<T0>(v0)();
      if (val0)
        return val0;
      else
        return std::forward<T1>(v1)();
    }

    DEFINE_FUNCTOR(pythonic::__builtin__::pythran, or_);
  }
}
PYTHONIC_NS_END

#endif
