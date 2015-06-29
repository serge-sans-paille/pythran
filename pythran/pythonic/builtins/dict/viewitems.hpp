#ifndef PYTHONIC_BUILTIN_DICT_VIEWITEMS_HPP
#define PYTHONIC_BUILTIN_DICT_VIEWITEMS_HPP

#include "pythonic/include/builtins/dict/viewitems.hpp"

#include "pythonic/types/dict.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace dict
    {

      template <class K, class V>
      types::dict_items<types::dict<K, V>> viewitems(types::dict<K, V> const &d)
      {
        return d.viewitems();
      }

      PROXY_IMPL(pythonic::builtins::dict, viewitems);
    }
  }
}

#endif
