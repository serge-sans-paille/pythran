#ifndef PYTHONIC_INCLUDE_BUILTIN_DICT_ITEMS_HPP
#define PYTHONIC_INCLUDE_BUILTIN_DICT_ITEMS_HPP

#include "pythonic/include/types/dict.hpp"
#include "pythonic/include/types/list.hpp"
#include "pythonic/include/utils/proxy.hpp"

#include <tuple>

namespace pythonic
{

  namespace builtins
  {

    namespace dict
    {

      template <class K, class V>
      types::list<std::tuple<K, V>> items(types::dict<K, V> const &d);

      PROXY_DECL(pythonic::builtins::dict, items);
    }
  }
}

#endif
