#ifndef PYTHONIC_INCLUDE_BUILTIN_DICT_KEYS_HPP
#define PYTHONIC_INCLUDE_BUILTIN_DICT_KEYS_HPP

#include "pythonic/include/types/dict.hpp"
#include "pythonic/include/types/list.hpp"
#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace dict
    {

      template <class K, class V>
      types::list<K> keys(types::dict<K, V> const &d);

      PROXY_DECL(pythonic::__builtin__::dict, keys);
    }
  }
}

#endif
