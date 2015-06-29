#ifndef PYTHONIC_BUILTIN_DICT_VIEWKEYS_HPP
#define PYTHONIC_BUILTIN_DICT_VIEWKEYS_HPP

#include "pythonic/include/builtins/dict/viewkeys.hpp"

#include "pythonic/types/dict.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace dict
    {

      template <class K, class V>
      types::dict_keys<types::dict<K, V>> viewkeys(types::dict<K, V> const &d)
      {
        return d.viewkeys();
      }

      PROXY_IMPL(pythonic::builtins::dict, viewkeys);
    }
  }
}

#endif
