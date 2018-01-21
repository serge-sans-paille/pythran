#ifndef PYTHONIC_INCLUDE_BUILTIN_DICT_ITERKEYS_HPP
#define PYTHONIC_INCLUDE_BUILTIN_DICT_ITERKEYS_HPP

#include "pythonic/include/types/dict.hpp"
#include "pythonic/include/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  namespace dict
  {
    template <class K, class V>
    auto iterkeys(types::dict<K, V> d) -> decltype(d.iterkeys());

    DECLARE_FUNCTOR(pythonic::__builtin__::dict, iterkeys);
  }
}
PYTHONIC_NS_END

#endif
