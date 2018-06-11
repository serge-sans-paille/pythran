#ifndef PYTHONIC_BUILTIN_PYTHRAN_IS_NONE_HPP
#define PYTHONIC_BUILTIN_PYTHRAN_IS_NONE_HPP

#include "pythonic/include/__builtin__/pythran/is_none.hpp"
#include "pythonic/utils/functor.hpp"
#include "pythonic/types/NoneType.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  namespace pythran
  {
    DEFINE_FUNCTOR(pythonic::__builtin__::pythran, is_none);
  }
}

PYTHONIC_NS_END

#endif
