#ifndef PYTHONIC_BUILTIN_DICT_ITERKEYS_HPP
#define PYTHONIC_BUILTIN_DICT_ITERKEYS_HPP

#include "pythonic/include/__builtin__/dict/iterkeys.hpp"

#include "pythonic/types/dict.hpp"
#include "pythonic/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  namespace dict
  {
    // We need a copy here for lvalue like :
    // for i in {"a": "b", "c": "d"}.iterkeys():
    //     pass
    template <class D>
    auto iterkeys(D &&d) -> decltype(std::forward<D>(d).iterkeys())
    {
      return std::forward<D>(d).iterkeys();
    }
  }
}
PYTHONIC_NS_END

#endif
