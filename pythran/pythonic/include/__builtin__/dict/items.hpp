#ifndef PYTHONIC_INCLUDE_BUILTIN_DICT_ITEMS_HPP
#define PYTHONIC_INCLUDE_BUILTIN_DICT_ITEMS_HPP

#include "pythonic/include/types/dict.hpp"
#include "pythonic/include/types/list.hpp"
#include "pythonic/include/utils/functor.hpp"

#include <tuple>

namespace pythonic
{

  namespace __builtin__
  {

    namespace dict
    {

      template <class K, class V>
      types::list<std::tuple<K, V>> items(types::dict<K, V> const &d);

      DECLARE_FUNCTOR(pythonic::__builtin__::dict, items);
    }
  }
}

#endif
