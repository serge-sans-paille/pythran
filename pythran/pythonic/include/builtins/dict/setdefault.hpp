#ifndef PYTHONIC_INCLUDE_BUILTIN_DICT_SETDEFAULT_HPP
#define PYTHONIC_INCLUDE_BUILTIN_DICT_SETDEFAULT_HPP

#include "pythonic/include/types/dict.hpp"
#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace dict
    {

      template <class K, class V, class W, class X>
      V setdefault(types::dict<K, V> &d, W const &k, X const &default_);

      template <class K, class V, class W>
      V setdefault(types::dict<K, V> &d, W const &k);

      template <class K, class V, class W, class X>
      V setdefault(types::dict<K, V> &&d, W const &k, X const &default_);

      template <class K, class V, class W>
      V setdefault(types::dict<K, V> &&d, W const &k);

      PROXY_DECL(pythonic::builtins::dict, setdefault);
    }
  }
}

#endif
