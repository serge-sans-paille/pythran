#ifndef PYTHONIC_BUILTIN_DICT_ITERITEMS_HPP
#define PYTHONIC_BUILTIN_DICT_ITERITEMS_HPP

#include "pythonic/include/__builtin__/dict/iteritems.hpp"

#include "pythonic/types/dict.hpp"
#include "pythonic/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  namespace dict
  {

    // See iterkeys for copy explication && TODOs
    template <class K, class V>
    auto iteritems(types::dict<K, V> d) -> decltype(d.iteritems())
    {
      return d.iteritems();
    }

    DEFINE_FUNCTOR(pythonic::__builtin__::dict, iteritems);
  }
}
PYTHONIC_NS_END

#endif
