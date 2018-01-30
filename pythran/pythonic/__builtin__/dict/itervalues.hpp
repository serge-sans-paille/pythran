#ifndef PYTHONIC_BUILTIN_DICT_ITERVALUES_HPP
#define PYTHONIC_BUILTIN_DICT_ITERVALUES_HPP

#include "pythonic/include/__builtin__/dict/itervalues.hpp"

#include "pythonic/types/dict.hpp"
#include "pythonic/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  namespace dict
  {

    // See iterkeys for copy explication && TODOs
    template <class K, class V>
    auto itervalues(types::dict<K, V> d) -> decltype(d.itervalues())
    {
      return d.itervalues();
    }

    DEFINE_FUNCTOR(pythonic::__builtin__::dict, itervalues);
  }
}
PYTHONIC_NS_END

#endif
