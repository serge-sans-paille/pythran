#ifndef PYTHONIC_INCLUDE_BUILTIN_DICT_ITERVALUES_HPP
#define PYTHONIC_INCLUDE_BUILTIN_DICT_ITERVALUES_HPP

#include "pythonic/types/dict.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace dict
    {

      template <class K, class V>
      auto itervalues(types::dict<K, V> d) -> decltype(d.itervalues());

      PROXY_DECL(pythonic::builtins::dict, itervalues);
    }
  }
}

#endif
