#ifndef PYTHONIC_INCLUDE_BUILTIN_DICT_POPITEM_HPP
#define PYTHONIC_INCLUDE_BUILTIN_DICT_POPITEM_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/dict.hpp"

#include <tuple>

namespace pythonic
{

  namespace __builtin__
  {

    namespace dict
    {

      template <class K, class V>
      std::tuple<K, V> popitem(types::dict<K, V> &d);

      template <class K, class V>
      std::tuple<K, V> popitem(types::dict<K, V> &&d);

      DECLARE_FUNCTOR(pythonic::__builtin__::dict, popitem);
    }
  }
}

#endif
