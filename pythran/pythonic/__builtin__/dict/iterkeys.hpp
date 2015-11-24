#ifndef PYTHONIC_BUILTIN_DICT_ITERKEYS_HPP
#define PYTHONIC_BUILTIN_DICT_ITERKEYS_HPP

#include "pythonic/include/__builtin__/dict/iterkeys.hpp"

#include "pythonic/types/dict.hpp"
#include "pythonic/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace dict
    {
      // We need a copy here for lvalue like :
      // for i in {"a": "b", "c": "d"}.iterkeys():
      //     pass
      // TODO : Could be fix if we provide an overload as it is "costly"
      // (shared ptr copying) while it is really a corner case
      // FIXME : Copy here is not enough to keep the dict alive!!
      template <class K, class V>
      auto iterkeys(types::dict<K, V> d) -> decltype(d.iterkeys())
      {
        return d.iterkeys();
      }

      DEFINE_FUNCTOR(pythonic::__builtin__::dict, iterkeys);
    }
  }
}

#endif
