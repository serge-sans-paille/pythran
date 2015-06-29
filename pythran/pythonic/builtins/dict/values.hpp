#ifndef PYTHONIC_BUILTIN_DICT_VALUES_HPP
#define PYTHONIC_BUILTIN_DICT_VALUES_HPP

#include "pythonic/include/builtins/dict/values.hpp"

#include "pythonic/types/dict.hpp"
#include "pythonic/types/list.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace dict
    {

      template <class K, class V>
      types::list<V> values(types::dict<K, V> const &d)
      {
        return {d.value_begin(), d.value_end()};
      }

      PROXY_IMPL(pythonic::builtins::dict, values);
    }
  }
}

#endif
