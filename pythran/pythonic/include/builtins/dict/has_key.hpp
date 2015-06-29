#ifndef PYTHONIC_INCLUDE_BUILTIN_DICT_HASKEY_HPP
#define PYTHONIC_INCLUDE_BUILTIN_DICT_HASKEY_HPP

#include "pythonic/include/types/dict.hpp"
#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace dict
    {

      template <class K, class V, class W>
      bool has_key(types::dict<K, V> const &d, W const &k);

      PROXY_DECL(pythonic::builtins::dict, has_key);
    }
  }
}

#endif
