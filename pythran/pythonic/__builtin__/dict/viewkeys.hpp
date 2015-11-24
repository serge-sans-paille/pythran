#ifndef PYTHONIC_BUILTIN_DICT_VIEWKEYS_HPP
#define PYTHONIC_BUILTIN_DICT_VIEWKEYS_HPP

#include "pythonic/include/__builtin__/dict/viewkeys.hpp"

#include "pythonic/types/dict.hpp"
#include "pythonic/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace dict
    {

      template <class K, class V>
      types::dict_keys<types::dict<K, V>> viewkeys(types::dict<K, V> const &d)
      {
        return d.viewkeys();
      }

      DEFINE_FUNCTOR(pythonic::__builtin__::dict, viewkeys);
    }
  }
}

#endif
