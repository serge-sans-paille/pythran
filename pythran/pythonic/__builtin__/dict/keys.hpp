#ifndef PYTHONIC_BUILTIN_DICT_KEYS_HPP
#define PYTHONIC_BUILTIN_DICT_KEYS_HPP

#include "pythonic/include/__builtin__/dict/keys.hpp"

#include "pythonic/types/dict.hpp"
#include "pythonic/types/list.hpp"
#include "pythonic/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  namespace dict
  {

    template <class K, class V>
    types::list<K> keys(types::dict<K, V> const &d)
    {
      return {d.key_begin(), d.key_end()};
    }

    DEFINE_FUNCTOR(pythonic::__builtin__::dict, keys);
  }
}
PYTHONIC_NS_END

#endif
