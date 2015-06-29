#ifndef PYTHONIC_INCLUDE_BUILTIN_DICT_POPITEM_HPP
#define PYTHONIC_INCLUDE_BUILTIN_DICT_POPITEM_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/types/dict.hpp"

#include <tuple>

namespace pythonic
{

  namespace builtins
  {

    namespace dict
    {

      template <class K, class V>
      std::tuple<K, V> popitem(types::dict<K, V> &d);

      template <class K, class V>
      std::tuple<K, V> popitem(types::dict<K, V> &&d);

      PROXY_DECL(pythonic::builtins::dict, popitem);
    }
  }
}

#endif
