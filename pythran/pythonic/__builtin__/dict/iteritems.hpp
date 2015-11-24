#ifndef PYTHONIC_BUILTIN_DICT_ITERITEMS_HPP
#define PYTHONIC_BUILTIN_DICT_ITERITEMS_HPP

#include "pythonic/include/__builtin__/dict/iteritems.hpp"

#include "pythonic/types/dict.hpp"
#include "pythonic/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace dict
    {

      // See iterkeys for copy explication and TODOs
      template <class K, class V>
      auto iteritems(types::dict<K, V> d) -> decltype(d.iteritems())
      {
        return d.iteritems();
      }

      DEFINE_FUNCTOR(pythonic::__builtin__::dict, iteritems);
    }
  }
}

#endif
