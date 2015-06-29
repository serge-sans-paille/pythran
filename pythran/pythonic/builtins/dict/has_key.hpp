#ifndef PYTHONIC_BUILTIN_DICT_HASKEY_HPP
#define PYTHONIC_BUILTIN_DICT_HASKEY_HPP

#include "pythonic/include/builtins/dict/has_key.hpp"

#include "pythonic/types/dict.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace dict
    {
      template <class K, class V, class W>
      bool has_key(types::dict<K, V> const &d, W const &k)
      {
        return d.find(k) != d.item_end();
      }

      PROXY_IMPL(pythonic::builtins::dict, has_key);
    }
  }
}

#endif
