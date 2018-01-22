#ifndef PYTHONIC_INCLUDE_BUILTIN_DICT_VIEWITEMS_HPP
#define PYTHONIC_INCLUDE_BUILTIN_DICT_VIEWITEMS_HPP

#include "pythonic/include/types/dict.hpp"
#include "pythonic/include/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  namespace dict
  {

    template <class K, class V>
    types::dict_items<types::dict<K, V>> viewitems(types::dict<K, V> const &d);

    DECLARE_FUNCTOR(pythonic::__builtin__::dict, viewitems);
  }
}
PYTHONIC_NS_END

#endif
