#ifndef PYTHONIC_BUILTIN_DICT_ITERVALUES_HPP
#define PYTHONIC_BUILTIN_DICT_ITERVALUES_HPP

#include "pythonic/include/builtins/dict/itervalues.hpp"

#include "pythonic/types/dict.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace dict
    {

      // See iterkeys for copy explication and TODOs
      template <class K, class V>
      auto itervalues(types::dict<K, V> d) -> decltype(d.itervalues())
      {
        return d.itervalues();
      }

      PROXY_IMPL(pythonic::builtins::dict, itervalues);
    }
  }
}

#endif
