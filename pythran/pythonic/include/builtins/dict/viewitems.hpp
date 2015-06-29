#ifndef PYTHONIC_INCLUDE_BUILTIN_DICT_VIEWITEMS_HPP
#define PYTHONIC_INCLUDE_BUILTIN_DICT_VIEWITEMS_HPP

#include "pythonic/include/types/dict.hpp"
#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace dict
    {

      template <class K, class V>
      types::dict_items<types::dict<K, V>>
      viewitems(types::dict<K, V> const &d);

      PROXY_DECL(pythonic::builtins::dict, viewitems);
    }
  }
}

#endif
