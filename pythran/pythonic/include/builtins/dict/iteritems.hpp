#ifndef PYTHONIC_INCLUDE_BUILTIN_DICT_ITERITEMS_HPP
#define PYTHONIC_INCLUDE_BUILTIN_DICT_ITERITEMS_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/types/dict.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace dict
    {

      template <class K, class V>
      auto iteritems(types::dict<K, V> d) -> decltype(d.iteritems());

      PROXY_DECL(pythonic::builtins::dict, iteritems);
    }
  }
}

#endif
