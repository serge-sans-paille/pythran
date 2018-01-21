#ifndef PYTHONIC_BUILTIN_DICT_VIEWVALUES_HPP
#define PYTHONIC_BUILTIN_DICT_VIEWVALUES_HPP

#include "pythonic/include/__builtin__/dict/viewvalues.hpp"

#include "pythonic/types/dict.hpp"
#include "pythonic/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  namespace dict
  {

    template <class K, class V>
    types::dict_values<types::dict<K, V>> viewvalues(types::dict<K, V> const &d)
    {
      return d.viewvalues();
    }

    DEFINE_FUNCTOR(pythonic::__builtin__::dict, viewvalues);
  }
}
PYTHONIC_NS_END

#endif
