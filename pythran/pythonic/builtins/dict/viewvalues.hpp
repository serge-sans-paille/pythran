#ifndef PYTHONIC_BUILTIN_DICT_VIEWVALUES_HPP
#define PYTHONIC_BUILTIN_DICT_VIEWVALUES_HPP

#include "pythonic/include/builtins/dict/viewvalues.hpp"

#include "pythonic/types/dict.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace dict
    {

      template <class K, class V>
      types::dict_values<types::dict<K, V>>
      viewvalues(types::dict<K, V> const &d)
      {
        return d.viewvalues();
      }

      PROXY_IMPL(pythonic::builtins::dict, viewvalues);
    }
  }
}

#endif
