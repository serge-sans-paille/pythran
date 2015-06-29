#ifndef PYTHONIC_BUILTIN_DICT_KEYS_HPP
#define PYTHONIC_BUILTIN_DICT_KEYS_HPP

#include "pythonic/include/builtins/dict/keys.hpp"

#include "pythonic/types/dict.hpp"
#include "pythonic/types/list.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace dict
    {

      template <class K, class V>
      types::list<K> keys(types::dict<K, V> const &d)
      {
        return {d.key_begin(), d.key_end()};
      }

      PROXY_IMPL(pythonic::builtins::dict, keys);
    }
  }
}

#endif
