#ifndef PYTHONIC_INCLUDE_BUILTIN_DICT_VALUES_HPP
#define PYTHONIC_INCLUDE_BUILTIN_DICT_VALUES_HPP

#include "pythonic/include/types/dict.hpp"
#include "pythonic/include/types/list.hpp"
#include "pythonic/include/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  namespace dict
  {
    template <class K, class V>
    types::list<V> values(types::dict<K, V> const &d);

    DECLARE_FUNCTOR(pythonic::__builtin__::dict, values);
  }
}
PYTHONIC_NS_END

#endif
