#ifndef PYTHONIC_INCLUDE_BUILTIN_DICT_VIEWVALUES_HPP
#define PYTHONIC_INCLUDE_BUILTIN_DICT_VIEWVALUES_HPP

#include "pythonic/include/types/dict.hpp"
#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace dict
    {

      template <class K, class V>
      types::dict_values<types::dict<K, V>>
      viewvalues(types::dict<K, V> const &d);

      PROXY_DECL(pythonic::builtins::dict, viewvalues);
    }
  }
}

#endif
