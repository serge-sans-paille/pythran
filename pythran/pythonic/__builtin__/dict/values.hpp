#ifndef PYTHONIC_BUILTIN_DICT_VALUES_HPP
#define PYTHONIC_BUILTIN_DICT_VALUES_HPP

#include "pythonic/include/__builtin__/dict/values.hpp"

#include "pythonic/types/dict.hpp"
#include "pythonic/types/list.hpp"
#include "pythonic/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace dict
    {

      template <class K, class V>
      types::list<V> values(types::dict<K, V> const &d)
      {
        return {d.value_begin(), d.value_end()};
      }

      DEFINE_FUNCTOR(pythonic::__builtin__::dict, values);
    }
  }
}

#endif
