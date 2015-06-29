#ifndef PYTHONIC_BUILTIN_DICT_POPITEM_HPP
#define PYTHONIC_BUILTIN_DICT_POPITEM_HPP

#include "pythonic/include/builtins/dict/popitem.hpp"

#include "pythonic/types/dict.hpp"
#include "pythonic/utils/proxy.hpp"

#include <tuple>

namespace pythonic
{

  namespace builtins
  {

    namespace dict
    {

      template <class K, class V>
      std::tuple<K, V> popitem(types::dict<K, V> &d)
      {
        return d.popitem();
      }

      template <class K, class V>
      std::tuple<K, V> popitem(types::dict<K, V> &&d)
      {
        return d.popitem();
      }

      PROXY_IMPL(pythonic::builtins::dict, popitem);
    }
  }
}

#endif
