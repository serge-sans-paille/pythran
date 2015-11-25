#ifndef PYTHONIC_BUILTIN_DICT_POPITEM_HPP
#define PYTHONIC_BUILTIN_DICT_POPITEM_HPP

#include "pythonic/include/__builtin__/dict/popitem.hpp"

#include "pythonic/types/dict.hpp"
#include "pythonic/utils/functor.hpp"

#include <tuple>

namespace pythonic
{

  namespace __builtin__
  {

    namespace dict
    {

      template <class K, class V>
      std::tuple<K, V> popitem(types::dict<K, V> &d)
      {
        return d.popitem();
      }

      template <class K, class V>
      std::tuple<K, V> popitem(types::dict<K, V> &&d)
      {
        return d.popitem();
      }

      DEFINE_FUNCTOR(pythonic::__builtin__::dict, popitem);
    }
  }
}

#endif
